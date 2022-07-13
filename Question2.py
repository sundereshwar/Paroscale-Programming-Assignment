import os

if os.path.exists('PSOutput.txt'):
    os.system("rm -rf PSOutput.txt")
    os.system("touch PSOutput.txt")

os.system("ps -ef >> PSOutput.txt")
os.system("cat PSOutput.txt | awk '/[*]*/{print $2}'")
