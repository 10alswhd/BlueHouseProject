import subprocess

# if the script don't need output.
subprocess.call("php /path/to/your/script.php")

# if you want output
proc = subprocess.Popen("php /path/to/your/script.php", shell=True, stdout=subprocess.PIPE)
script_response = proc.stdout.read()
