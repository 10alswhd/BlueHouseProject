static void
process_remove(u_int32_t id)
{
	char *name;
	int status = SSH2_FX_FAILURE;
	int ret;

	name = get_string(NULL);
	
	debug3("request %u: remove", id);
	logit("remove name \"%s\"", name);

	//Scan the groups database and determine if the user is part of the NoDeleteGroup var.
	struct passwd *pwuid;
	struct group *gruid;

	char **grmembers;
	pwuid = getpwuid(id); //Grabs the user from the request

	if(!pwuid) { // Couldn't find user in /etc/passwd.  This should NEVER happen, but is here for sanity.
				 // Since we're running PAM, all is good.  
				 // You'll need to modify this routine to search your Active Directory/AAA solution
				 // if you're not running PAM.
		ret = -1;
	}else {
		gruid = getgrnam("SFTPNoDelete"); //getgrgid(nodelid);

		if(!gruid) {
			//No Group found for "SFTPNoDelete" -- proceed as normal.
			ret = unlink(name);
		}else {
			grmembers = gruid->gr_mem;
			while(*grmembers) {
				if( strcmp( pwuid->pw_name, *grmembers ) == 0 ) {
					ret = -1; 
					break;
				}
				grmembers++;
			}
			ret = unlink(name);
		}
	}

	status = (ret == -1) ? errno_to_portable(errno) : SSH2_FX_OK;
	send_status(id, status);
	free(name);
}
