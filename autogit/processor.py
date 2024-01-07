from autogit.utils import execsh, perror, get_bold_yellow_str, append_stop, log_success, get_cyan_str, get_bold_blue_str
from autogit import sys

"""
make_commit()->int function makes commit
it has a few return keys we should care about
1 -> everything is ok and commit is successful
2 -> couldn't execute git commit -m
3 ->  no commit was made thus skipped
"""

def make_commit()->int:
    print(get_cyan_str("attempting to make commit"))
    return_code, stdout, stderr = execsh("git add .")
    if return_code == 0:
        commit_msg  = generate_commit_message()
        if commit_msg:
            exit_stat,stdout, _ = execsh(f'git commit -m "{commit_msg}"')
            if exit_stat == 0:
                log_success("commit added", True)
                return 1
                
            else:
                perror("autogit: fatal error: couldn't execute git commit -m")
                print(stdout)
                return 2
        else:
            return 3
                
    else:
        if "not a git repository" in stderr:
            perror("autogit: fatal error, not a git repository; make sure to run git init ")
            sys.exit(1)
        else:
            perror("autogit: fatal error, couldn't execute git .")
            sys.exit(1)
    
        
    

def generate_commit_message()-> str:
    return_code, stdout, stderr = execsh("git status")
    if return_code == 0:
        if "nothing to commit, working tree clean" in stdout:
            print(get_bold_yellow_str("nothing to commit (skipped)"))
            return None
        else:
            commit_message  = parse_raw_status(stdout)
            return commit_message
    else: 
        perror("autogit: fatal error: couldn't execute git status")
        sys.exit(1)


"""
We are basically gonna be detecting 3 keywords here
* modified
* new file
* deleted
* renamed:
"""


def parse_raw_status(raw_stat : str)->str:
    lines = raw_stat.split("\n")
    modifieds = []
    new_files = []
    deletes = []
    renames= []
    for index, line in enumerate(lines):
        if "modified:" in line or "new file:" in line or "deleted:" in line or "renamed:" in line:
            __split_line = line.split(":", 1)
            if len(__split_line) >1:
            # print(__split_line)
                line_kv: dict  = {
                    "mode": __split_line[0],
                    "file": __split_line[1]
                }
            else:
                perror("autogit: fatal error (couldn't parse git status stdout)")
                exit(1)
            if  "modified" in line_kv["mode"]:
                modifieds.append(line_kv["file"].strip())
            elif "new file" in line_kv["mode"]:
                new_files.append(line_kv["file"].strip())
            elif "deleted" in line_kv["mode"]:
                deletes.append(line_kv["file"].strip()) 
            elif "renamed" in line_kv["mode"]:
                renames.append(line_kv["file"].strip()) 

    msg_new_files = ""
    msg_modifieds = ""
    msg_deletes = ""
    msg_renames = ""
    if len(new_files) > 0:
        msg_new_files = "Added " + ", ".join(new_files)
    
    if len(modifieds) > 0:
        msg_modifieds = "Updated " + ", ".join(modifieds)
    if len(deletes) > 0:
        msg_deletes = "Deleted " + ", ".join(deletes)
    
    if len(renames) > 0:
        msg_renames = "Renamed " + ", ".join(renames)
    commit_message = append_stop(msg_modifieds, "; ") + append_stop(msg_new_files, "; ") + append_stop(msg_renames, "; ") +append_stop(msg_deletes, ";") 
    return commit_message


"""
 The make_push() function will try to push in remote repository.
 First we check if remote repo is available or not
 Same return convention for make_commit() is applicable here meaning
 1 -> everything is ok and commit is successful
 2 -> couldn't execute git commit -m
 3 ->  no commit was made thus skipped
"""


def make_push():
    # first let's make a commit call first
    commit = make_commit()
    if commit == 3:
        print(get_bold_blue_str("No changes for push (skipped)"))
        return 3
    elif commit == 2:
        perror("autogit: commit failed(autopush skipped)")
        return 2
    # check if remote repo is available 
    print(get_cyan_str("Pushing commit changes..."))
    return_code,stdout,err =  execsh("git remote -v")
    if return_code != 0:
        perror("autogit: fatal error: couldn't execute git remote -v")
        perror(err)
        exit(1)
    
    if len(stdout) > 0:
        exit_status, push_stdout, push_err = execsh("git push")
        if exit_status != 0:
            perror("autogit: fatal error: execution failed for git push")
            perror(push_err)
            exit(101)
        if "Everything up-to-date" in push_stdout:
            print(get_bold_blue_str("No changes for push (skipped)"))
            return 3
        else:
            # at this point we just pray and assume everything's okey and the repo is pushed
            log_success("local commit have been pushed to remote", True)
            return 1
    else:
        perror("please add git remote origin before calling auto push")
        exit(150)
    