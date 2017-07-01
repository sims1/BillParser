import os
import subprocess

astyleCommand = ['/Users/ling/GitHub/astyle/build/gcc/bin/astyle', '--style=kr', '--indent=spaces=4', '--min-conditional-indent=0', '--max-instatement-indent=80', '--align-pointer=name', '--align-reference=name', '--indent-switches', '--indent-cases', '--indent-labels', '--indent-preproc-define', '--indent-col1-comments', '--pad-header', '--convert-tabs', '--mode=c', '--lineend=linux']


def getCommitList():
    lines = subprocess.check_output(['git', 'status']).replace('\t', '').split('\n')
    lines = lines[6:]
    ret = []
    currentpath = os.getcwd()
    for line in lines:
        if line == '' or \
           'Untracked files:' in line or \
           'git add <file>...' in line or \
           'git add" and/or "git commit -a' in line:
            continue
        tagList = ['add:', 'modified: ']
        for tag in tagList:
            if tag in line:
                ret.append(os.path.join(currentpath, line.replace(tag, '').replace(' ', '')))
    return ret

def applyCommand(fileList, command):
    for f in fileList:
        if f.endswith('.vcxproj') and 'dos2unix' in command:
            continue
        subprocess.call(command + [f])

def checkSuffix(str):
    return str.endswith('.hpp') or str.endswith('.cpp')
        
def main():
    commitList = getCommitList()
    #commitList = [
    #'sources/cxx_lef/mir/prettyPrinter/BasicBlockConverter.cpp',
    #]

    print '\ncommit Files:\n======================'
    for f in commitList:
        print f

    cppList = list(filter(lambda x: checkSuffix(x),  commitList))
    applyCommand(cppList, astyleCommand)
    '''
    applyCommand(commitList, ['chmod', '0644'])
    applyCommand(commitList, ['git', 'add'])

    subprocess.call(['git', 'status'])
'''
if __name__ == '__main__':
    main()


