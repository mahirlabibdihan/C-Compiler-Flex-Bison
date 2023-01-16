import os, fnmatch

def findReplace(directory, find, replace, filePattern):
    for path, dirs, files in os.walk(os.path.abspath(directory)):
        for filename in fnmatch.filter(files, filePattern):
            filepath = os.path.join(path, filename)
            with open(filepath) as f:
                s = f.read()
            s = s.replace(find, replace)
            with open(filepath, "w") as f:
                f.write(s)

def renameFiles(directory, prefix, filePattern):
    for path, dirs, files in os.walk(os.path.abspath(directory)):
        for filename in fnmatch.filter(files, filePattern):
            os.rename(os.path.join(path, filename), os.path.join(path, prefix + filename))

def renameFile(directory, oldfile, newfile):
    os.rename(os.path.join(directory, oldfile), os.path.join(directory, newfile))
            
                

findReplace("upload/1905072/", "../include/", "1905072_", "*.cpp");
findReplace("upload/1905072/", "../include/", "1905072_", "*.hpp");
findReplace("upload/1905072/", "../include/", "1905072_", "*.l");

findReplace("upload/1905072/", "io/", "1905072_", "*.cpp");

renameFiles("upload/1905072/", "1905072_", "*.cpp");
renameFiles("upload/1905072/", "1905072_", "*.hpp");

renameFile("upload/1905072/", "scanner.l", "1905072.l");
