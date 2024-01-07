from autogit.utils import execsh, perror
def make_commit()->bool:
    return_code, stdout, stderr = execsh("git add .")
    if return_code == 0:
        generate_commit_message()
    else:
        if "not a git repository" in stderr:
            perror("autogit: fatal error, not a git repository; make sure to run git init ")
        else:
            perror("autogit: fatal error, couldn't execute git .")
        
    

def generate_commit_message()-> str:
    return_code, stdout, stderr = execsh("git status")
    if return_code == 0:
        print(stdout)
    else: 
        perror("autogit: fatal error: couldn't execute git status")