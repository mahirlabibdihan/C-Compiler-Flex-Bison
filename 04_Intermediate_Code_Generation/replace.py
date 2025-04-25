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

findReplace("upload/1905072/", "\"../include/", "\"1905072_", "*.cpp");
findReplace("upload/1905072/", "\"../include/", "\"1905072_", "*.hpp");
findReplace("upload/1905072/", "\"../include/", "\"1905072_", "1905072.l");
findReplace("upload/1905072/", "\"../include/", "\"1905072_", "1905072.y");