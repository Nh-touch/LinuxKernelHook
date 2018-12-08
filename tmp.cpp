
string GetMd5(string raw_data)
{
    return raw_data.substr(0, 32);
}

string GetRemotePath(string raw_data)
{
    return raw_data.substr(35);
}

bool IsFileExist(string path)
{
    return (_access(path.c_str(), 0) != -1);
}

string Md5ToLocalPath(string root, string md5)
{
    // root/md5prefix(2)/md5
    return string(root + string("/") + md5.substr(0, 2) + string("/") + md5);
}
