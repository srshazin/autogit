from autogit.utils import execsh, perror, get_bold_yellow_str, append_stop, log_success
from autogit import sys
def make_commit()->bool:
    return_code, stdout, stderr = execsh("git add .")
    if return_code == 0:
        commit_msg  = generate_commit_message()
        exit_stat,stdout, _ = execsh(f'git commit -m "{commit_msg}"')
        if exit_stat == 0:
            log_success("commit added", True)
        else:
            perror("autogit: fatal error: couldn't execute git commit -m")
            sys.exit(1)
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
        if len(line) > 0 and index > 4:
            __split_line = line.split(":", 1)
            # print(__split_line)
            line_kv: dict  = {
                "mode": __split_line[0],
                "file": __split_line[1]
            }
            if  "modified" in line_kv["mode"]:
                modifieds.append(line_kv["file"].strip())
                print("yes")
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
