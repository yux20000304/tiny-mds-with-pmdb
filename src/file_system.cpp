//
// Created by yyx on 2022/1/22.
//

#include "file_system.h"
#include "tools.h"
#include <vector>
#include <string>


using namespace std;

FileSystem::FileSystem(MetadataServer* metadata_server) {
    file_structure_ = new FileStructure(this);
    master_metadata_server = metadata_server;
}

FileSystem::~FileSystem() {
    delete file_structure_;
}

FileSystem* FileSystem::GetClassType(void) {
    return this;
}

void FileSystem::pwd(const vector<string>& command_args, string& feedback) {
    file_structure_->GetCurrentDirectory(feedback);
}

void FileSystem::mkdir(const vector<string>& command_args, string& feedback) {
    if (command_args.size() < 2) {
        feedback = "[ERROR] Command \"mkdir\" requires 1 argument.\n";
    }
    else {
        const string& name = command_args[1];
        file_structure_->MakeDirectory(name, feedback);
    }
}

bool CheckOptionArg(const string& arg) {
    if (arg.empty()) {
        Error("[ERROR] arg must not be empty.");
    }
    return arg[0] == '-';
}

void FileSystem::ls(const vector<string>&command_args, string& feedback) {
    string src = ".";
    bool recursive = false;
    int len = command_args.size();
    for (int i = 1; i < len; i++) {
        if (CheckOptionArg(command_args[i])) {
            if (command_args[i] == "-r") {
                recursive = true;
            }
            else {
                feedback = "[ERROR] Argument " + command_args[i] + " is not supported.\n";
            }
        }
        else {
            src = command_args[i];
        }
    }
    file_structure_->List(src, recursive, feedback);
}

void FileSystem::readdir(const vector<string>& command_args, string& feedback) {
    string src = ".";
    if (command_args.size() > 1) {
        src = command_args[1];
    }
    file_structure_->List(command_args[1], false, feedback);
}

void FileSystem::cd(const vector<string>& command_args, string& feedback)
{
    if (command_args.size() == 1) {
        feedback = "[ERROR] Command \"cd\" requires 1 argument.\n";
    }
    else {
        file_structure_->GoToDirectory(command_args[1], feedback);
    }
}

void FileSystem::mv(const vector<string>& command_args, string& feedback) {
    if (command_args.size() < 3) {
        feedback = "[ERROR] Command \"mv\" requires 2 argument.\n";
    }
    else {
        file_structure_->Move(command_args[1], command_args[2], feedback);
    }
}

void FileSystem::stat(const vector<string>& command_args, string& feedback) {
    if (command_args.size() == 1) {
        feedback = "[ERROR] Command \"stat\" requires 1 argument.\n";
    }
    else {
        file_structure_->State(command_args[1], feedback);
    }
}

void FileSystem::touch(const vector<string>& command_args, string& feedback)
{
    if (command_args.size() == 1) {
        feedback = "[ERROR] Command \"touch\" requires 1 argument.\n";
    }
    else {
        file_structure_->Touch(command_args[1], feedback);
    }
}

void FileSystem::rm(const vector<string>& command_args, string& feedback) {
    string src = "";
    bool recursive = false;
    int len = command_args.size();
    for (int i = 1; i < len; ++i) {
        if (CheckOptionArg(command_args[i])) {
            if (command_args[i] == "-r") {
                recursive = true;
            }
            else {
                feedback = "[ERROR] Argument " + command_args[i] + " is not supported.\n";
            }
        }
        else {
            src = command_args[i];
        }
    }
    if (src.empty()) {
        feedback = "[ERROR] Command \"rm\" requires 1 positional arguments.\n";
    }
    else {
        file_structure_->Remove(src, recursive, feedback);
    }
}

void FileSystem::serverstats(const vector<string>& command_args, string& feedback) {
    master_metadata_server->CheckSlaveStats(feedback);
}

void FileSystem::ExecuteCommand(const vector<string>& command_args, string& feedback) {
    if (command_args.empty()) {
        Error("[ERROR] Size of command_args should not be 0.\n");
    }
    const string& command = command_args[0];
    if (command == "pwd") {
        this->pwd(command_args, feedback);
    }
    else if (command == "mkdir") {
        this->mkdir(command_args, feedback);
    }
    else if (command == "ls") {
        this->ls(command_args, feedback);
    }
    else if (command == "readdir") {
        this->readdir(command_args, feedback);
    }
    else if (command == "cd") {
        this->cd(command_args, feedback);
    }
    else if (command == "mv") {
        this->mv(command_args, feedback);
    }
    else if (command == "stat") {
        this->stat(command_args, feedback);
    }
    else if (command == "touch") {
        this->touch(command_args, feedback);
    }
    else if (command == "rm") {
        this->rm(command_args, feedback);
    }
    else if (command == "serverstats") {
        this->serverstats(command_args, feedback);
    }
    else {
        feedback = "[ERROR] Command " + command + " is not supported.\n";
    }
}


vector<string> SplitPath(const string &path) {
    return SplitString(path, "/");;
}

string get_time() {
    time_t current_time = time(0);
    string current_time_string = string(ctime(&current_time));
    vector<string> time_parts;
    time_parts = SplitString(current_time_string);
    string result = time_parts[0];
    for (int i = 1; i < time_parts.size(); ++i) {
        result += ("-" + time_parts[i]);
    }
    return result;
}

int FileStructure::FileNode::node_count_ = 0;

FileStructure::FileNode::FileNode(FileStructure *file_structure, bool is_file):
        file_structure_(file_structure),
        object_id_(FileNode::node_count_++),
        is_file_(is_file) {
}

FileStructure::FileNode::FileNode(FileStructure *file_structure):
        FileNode(file_structure, false) {
    parent_ = nullptr;
    object_name_ = "~";
}

FileStructure::FileNode::FileNode(FileStructure *file_structure, FileNode *parent, const string &name, bool is_file, int size, string &feedback):
        FileNode(file_structure, is_file) {
    if (parent == nullptr) {
        Error("[ERROR] Parent should not be nullptr!");
    }
    parent_ = parent;
    object_name_ = name;
    string creation_message = this->GenerateCreationMessage();
    this->MasterCallSlavesHandleThisNode(creation_message, feedback);
}

void FileStructure::FileNode::MasterCallSlavesHandleThisNode(const string &message, string &feedback) const {
    if (object_id_ == 0) {
        Error("[ERROR] Should not let slaves handle root node!");
    }
    vector<int> slave_ids;
    file_structure_->file_system_->master_metadata_server->WhichSlaveToStore(object_id_, slave_ids);
    file_structure_->file_system_->master_metadata_server->SendMessageToSlaves(slave_ids, message, feedback);
}


string FileStructure::FileNode::GenerateCreationMessage() const {
    string result = "create ";
    result += to_string(object_id_);
    result += " ";
    if (parent_ == nullptr) {
        result += "-1 ";
    }
    else {
        result += to_string(parent_->get_object_id());
        result += " ";
    }
    string time_string = get_time();
    stringstream message_stream;
    message_stream << time_string << " " << time_string << " 0 " << object_name_ << " " << string(is_file_ ? "1" : "0") << " ";
    result += message_stream.str();
    return result;
}

const string& FileStructure::FileNode::get_object_name() const {
    return object_name_;
}

FileStructure::FileNode* const& FileStructure::FileNode::get_parent() const {
    return parent_;
}

const vector<FileStructure::FileNode*>& FileStructure::FileNode::get_children() const {
    return children_;
}

int FileStructure::FileNode::FindChildIndex(const string &child_name) const {
    int len = children_.size();
    for (int i = 0; i < len; ++i) {
        if (children_[i]->object_name_ == child_name) {
            return i;
        }
    }
    return -1;
}

void FileStructure::FileNode::FindNearbyDirectory(const string &name, FileNode *&result) {
    if (name == "..") {
        result = parent_;
    }
    else if (name == ".") {
        result = this;
    }
    else {
        int id = this->FindChildIndex(name);
        if (id < 0) {
            result = nullptr;
        }
        else {
            result = children_[id];
        }
    }
}

FileStructure::FileStructure(FileSystem *file_system): file_system_(file_system) {
    root_node_ = new FileNode(this);
    current_node_ = root_node_;
}

void FileStructure::FileNode::DetachSelfFromParent() {
    int sibling_num = parent_->children_.size();
    for (int i = 0; i < sibling_num; ++i) {
        if (parent_->children_[i]->object_name_ == object_name_) {
            parent_->children_.erase(parent_->children_.begin() + i);
            break;
        }
    }
    parent_ = nullptr;
}

void FileStructure::FileNode::AttachToNewParent(FileNode *new_parent) {
    if (new_parent == nullptr) {
        Error("[ERROR] Parent must not be nullptr.\n");
    }
    else if (new_parent->is_file_) {
        Error("[ERROR] Parent node must not be a file.\n");
    }
    parent_ = new_parent;
    parent_->children_.push_back(this);
}

bool FileStructure::FileNode::is_file() const {
    return is_file_;
}

void FileStructure::FileNode::AttachTo(FileNode *new_parent, string &feedback) {
    this->DetachSelfFromParent();
    this->AttachToNewParent(new_parent);
    string message = this->GenerateUpdateMessage("parent", to_string(new_parent->object_id_));
    this->MasterCallSlavesHandleThisNode(message, feedback);
}

FileStructure::FileNode* const& FileStructure::FileNode::AddChild(const string &name, bool is_file, int size, string &feedback) {
    if (is_file_) {
        Error("[Error] File must not have a child.\n");
    }
    FileNode *child = new FileNode(file_structure_, this, name, is_file, size, feedback);
    children_.push_back(child);
    return children_.back();
}

void FileStructure::FileNode::set_object_name_(const string &new_name, string &feedback) {
    object_name_ = new_name;
    string message = this->GenerateUpdateMessage("name", new_name);
    this->MasterCallSlavesHandleThisNode(message, feedback);
}

void FileStructure::FileNode::RemoveChild(int child_index, string &feedback) {
    string message = "delete " + to_string(children_[child_index]->object_id_);
    children_[child_index]->MasterCallSlavesHandleThisNode(message, feedback);
    delete children_[child_index];
    children_.erase(children_.begin() + child_index);
}

void FileStructure::FileNode::RemoveChild(FileNode *child_node, string &feedback) {
    for (int i = 0;i < this -> children_.size(); ++i) {
        if (children_[i]->object_id_ == child_node->object_id_) {
            this->RemoveChild(i, feedback);
            return;
        }
    }
    Error("[ERROR] The node to be removed is not a child of this.\n");
}

string FileStructure::FileNode::GenerateUpdateMessage(const string &key, const string &value) const {
    return "update " + to_string(object_id_) + " " + key + " " + value;
}

void FileStructure::FileNode::RefreshTime(string &feedback) {
    string time_string = get_time();
    string message = this->GenerateUpdateMessage("modification_time", time_string);
    this->MasterCallSlavesHandleThisNode(message, feedback);
}

const int FileStructure::FileNode::get_object_id() const {
    return object_id_;
}

void FileStructure::FileNode::RequestSelf(string &feedback) const {
    string message = "request " + to_string(object_id_);
    this->MasterCallSlavesHandleThisNode(message, feedback);
}

void FileStructure::GetCurrentDirectory(string &feedback) {
    feedback = "\n";
    FileNode *local_node = current_node_;
    while (true) {
        feedback = local_node->get_object_name() + feedback;
        local_node = local_node->get_parent();
        if (local_node == nullptr) {
            break;
        }
        else {
            feedback = "/" + feedback;
        }
    }
}

void FileStructure::MakeDirectory(const string &path, string &feedback) {
    vector<string> path_args;
    path_args = SplitPath(path);
    FileNode *nodeholder = nullptr;
    if (!this->CreateDirectory(path_args, nodeholder, feedback)) {
        feedback = "[ERROR] " + path + " is impossible because it passes by some file.\n";
    }
}

bool FileStructure::CreateDirectory(const vector<string> &path_args, FileNode *&generated_node, string &feedback) {
    int len_paths = path_args.size();
    FileNode *self_node = current_node_;
    FileNode *tmp_node = nullptr;
    for (int i=0;i<len_paths;i++) {
        if (self_node->is_file()) {
            return false;
        }
        else {
            self_node->FindNearbyDirectory(path_args[i], tmp_node);
            if (tmp_node == nullptr) {
                tmp_node = self_node->AddChild(path_args[i], false, 0, feedback);
            }
            self_node = tmp_node;
        }
    }
    generated_node = self_node;
    return true;
}

void FileStructure::List(const string &path, bool recursive_flag, string &feedback) {
    vector<string> paths;
    paths = SplitPath(path);
    FileStructure::FileNode *dest = nullptr;
    if (IsValidPath(paths, current_node_, dest)) {
        if (recursive_flag) {
            vector<string> strs;
            RecursiveListObjects(dest, strs, "top");
            feedback = "";
            for (auto & str : strs) {
                feedback += str;
                feedback += "\n";
            }
        }
        else {
            int num_current_dirs = dest->get_children().size();
            for (int i=0;i<num_current_dirs;i++) {
                feedback += dest->get_children()[i]->get_object_name();
                feedback += "\n";
            }
        }
    }
    else {
        feedback = "[ERROR] directory ";
        feedback += path;
        feedback += " is not found.\n";
    }
}

void FileStructure::GoToDirectory(const string &path, string &feedback) {
    vector<string> paths;
    paths = SplitPath(path);
    FileNode *destholder = nullptr;
    if (this->IsValidPath(paths, current_node_, destholder)) {
        if (destholder->is_file()) {
            feedback = "[ERROR] ";
            feedback += path;
            feedback += " is a file.\n";
        }
        else {
            current_node_ = destholder;
        }
    }
    else {
        feedback = "[ERROR] directory ";
        feedback += path;
        feedback += " is not found.\n";
    }
}

void FileStructure::Move(const std::string &src_path, const std::string &dst_path, std::string &feedback) {
    vector<string> src_path_args, dst_path_args;
    src_path_args = SplitPath(src_path);
    dst_path_args = SplitPath(dst_path);
    FileNode *src_node = nullptr;
    FileNode *dst_node = nullptr;
    if (this->IsValidPath(src_path_args, current_node_, src_node)) {
        if (this->IsValidPath(dst_path_args, current_node_, dst_node)) {
            if (dst_node->is_file()) {
                feedback = "[ERROR] Destination ";
                feedback += dst_path;
                feedback += " is a file.\n";

            }
            else {
                if (dst_node->FindChildIndex(src_node->get_object_name()) >= 0) {
                    feedback = "[ERROR] File in ";
                    feedback += dst_path;
                    feedback += " has a same name.\n";
                }
                else {
                    src_node->AttachTo(dst_node, feedback);
                }
            }
        }
        else {
            vector<string> dst_parent_path_args;
            this->ParentPath(dst_path_args, dst_parent_path_args);
            if(this->CreateDirectory(dst_parent_path_args, dst_node, feedback)) {
                src_node->AttachTo(dst_node, feedback);
                src_node->set_object_name_(dst_path_args.back(), feedback);
            }
            else {
                feedback = "[ERROR] Path ";
                feedback += dst_path;
                feedback += " includes a file.\n";
            }
        }
    }
    else {
        feedback = "[ERROR] directory/file ";
        feedback += src_path;
        feedback += " is not found.\n";
    }
}

void FileStructure::State(const string &path, string &feedback) {
    vector<string> paths;
    paths = SplitPath(path);
    FileNode *dest_node = nullptr;
    if (this->IsValidPath(paths, current_node_, dest_node)) {
        dest_node->RequestSelf(feedback);
    }
    else {
        feedback = "[ERROR] directory/file ";
        feedback += path;
        feedback += " is not found.\n";
    }
}

void FileStructure::Touch(const string &path, string &feedback) {
    vector<string> path_args;
    path_args = SplitPath(path);
    FileNode *dst_node = nullptr;
    if (this->IsValidPath(path_args, current_node_, dst_node)) {
        dst_node->RefreshTime(feedback);
    }
    else {
        vector<string> parent_path_args;
        this->ParentPath(path_args, parent_path_args);
        if(this->CreateDirectory(parent_path_args, dst_node, feedback)) {
            dst_node->AddChild(path_args.back(), true, 0, feedback);
        }
        else {
            feedback = "[ERROR] Path ";
            feedback += path;
            feedback += " includes a file.\n";
        }
    }
}

void FileStructure::Remove(const std::string &path, bool recursive_flag, std::string &feedback) {
    vector<string> paths;
    paths = SplitPath(path);
    FileNode *tmp_node = nullptr;
    if (this->IsValidPath(paths, current_node_, tmp_node)) {
        if (tmp_node == root_node_) {
            feedback = "[ERROR] cannot delete the root.\n";
        }
        else if (tmp_node->is_file() || recursive_flag) {
            this->RecursiveRemoveChildren(tmp_node, feedback);
            tmp_node->get_parent()->RemoveChild(tmp_node, feedback);
        }
        else {
            feedback = "[ERROR] ";
            feedback += path;
            feedback += " is a directory. Use rm -r DIRNAME to remove it.\n";
        }
    }
    else {
        feedback = "[ERROR] File ";
        feedback += path;
        feedback += " not found.\n";
    }
}

bool FileStructure::IsValidPath(const vector<string> &path_args, FileNode *src_node, FileNode *&dst_node) {
    dst_node = src_node;
    for (const auto & path_arg : path_args) {
        dst_node->FindNearbyDirectory(path_arg, dst_node);
        if (dst_node == nullptr) {
            return false;
        }
    }
    return true;
}

void FileStructure::ParentPath(const vector<string>& path_args, vector<string>& result) {
    result.assign(path_args.begin(), path_args.end() - 1);
}

void FileStructure::RecursiveListObjects(const FileNode * const start_node, vector<string> &object_names, const string &last_level_indent) {
    string indent_name;
    string self_indent = last_level_indent;
    string current_level_indent = last_level_indent;

    if (last_level_indent == "top") {
        current_level_indent = "";
        indent_name = start_node->get_object_name();
    }
    else {
        if (start_node == start_node->get_parent()->get_children().back()) {
            self_indent += "└";
            self_indent += "─";
            self_indent += "─";
            self_indent += " ";
            current_level_indent += string(4, ' ');
        }
        else {
            self_indent += "├";
            self_indent += "─";
            self_indent += "─";
            self_indent += " ";
            current_level_indent += "│";
            current_level_indent += string(3, ' ');
        }
        indent_name += self_indent;
        indent_name += start_node->get_object_name();
    }
    if (!start_node->is_file()) {
        indent_name += "/";
    }
    object_names.push_back(indent_name);
    int num_current_dirs = start_node->get_children().size();
    for (int i = 0; i < num_current_dirs; ++i) {
        RecursiveListObjects(start_node->get_children()[i], object_names, current_level_indent);
    }
}

void FileStructure::RecursiveRemoveChildren(FileNode *start_node, string &feedback) {
    for(int i = 0; i < start_node->get_children().size(); ) {
        RecursiveRemoveChildren(start_node->get_children()[i], feedback);
        start_node->RemoveChild(i, feedback);
    }
}

FileStructure::~FileStructure() {
    string message;
    this->RecursiveRemoveChildren(root_node_, message);
    delete root_node_;
}
