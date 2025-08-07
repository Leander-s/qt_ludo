import os
import shutil


def make_game(root_dir, build_dir):
    os.chdir(build_dir)
    if (os.path.exists("shaders")):
        shutil.rmtree("shaders")
    if (os.path.exists("assets")):
        shutil.rmtree("assets")
    shutil.copytree("../shaders", "shaders")
    shutil.copytree("../assets", "assets")
    os.system("cmake -G Ninja ..")
    os.system("ninja")
    os.chdir(root_dir)


if __name__ == '__main__':
    make_game("../build")
