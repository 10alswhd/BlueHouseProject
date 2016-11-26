#include <windows.h>
#include <string.h>
#include <assert.h>
#include <iomanip>
#include <algorithm>
#include <string> 

typedef struct dirent
{
	char d_name[MAX_PATH + 1]; /* current dir entry (multi-byte char string) */
	WIN32_FIND_DATAA data;     /* file attributes */
}  dirent;


typedef struct DIR
{
	dirent current;            /* Current directory entry */
	int    cached;             /* Indicates un-processed entry in memory */
	HANDLE search_handle;      /* File search handle */
	char   patt[MAX_PATH + 3]; /* search pattern (3 = pattern + "\\*\0") */
} DIR;


/* Forward declarations */
static DIR *opendir (const char *dirname);
static struct dirent *readdir (DIR *dirp);
static int closedir (DIR *dirp);

#ifndef USE_VTK_COSMO
static void rewinddir(DIR* dirp);
#endif

/* Use the new safe string functions introduced in Visual Studio 2005 */
#if defined(_MSC_VER) && _MSC_VER >= 1400
# define STRNCPY(dest,src,size) strncpy_s((dest),(size),(src),_TRUNCATE)
#else
# define STRNCPY(dest,src,size) strncpy((dest),(src),(size))
#endif


/*****************************************************************************
* Open directory stream DIRNAME for read and return a pointer to the
* internal working area that is used to retrieve individual directory
* entries.
*/
static DIR *opendir(const char *dirname)
{
	DIR *dirp;
	assert (dirname != NULL);
	assert (strlen (dirname) < MAX_PATH);

	/* construct new DIR structure */
	dirp = (DIR*) malloc (sizeof (struct DIR));
	if (dirp != NULL) {
		char *p;

		/* take directory name... */
		STRNCPY (dirp->patt, dirname, sizeof(dirp->patt));
		dirp->patt[MAX_PATH] = '\0';

		/* ... and append search pattern to it */
		p = strchr (dirp->patt, '\0');
		if (dirp->patt < p  &&  *(p-1) != '\\'  &&  *(p-1) != ':') {
			*p++ = '\\';
		}
		*p++ = '*';
		*p = '\0';

		/* open stream and retrieve first file */
		dirp->search_handle = FindFirstFileA (dirp->patt, &dirp->current.data);
		if (dirp->search_handle == INVALID_HANDLE_VALUE) {
			/* invalid search pattern? */
			free (dirp);
			return NULL;
		}

		/* there is an un-processed directory entry in memory now */
		dirp->cached = 1;
	}

	return dirp;
}


/*****************************************************************************
* Read a directory entry, and return a pointer to a dirent structure
* containing the name of the entry in d_name field.  Individual directory
* entries returned by this very function include regular files,
* sub-directories, pseudo-directories "." and "..", but also volume labels,
* hidden files and system files may be returned.
*/
static struct dirent *readdir(DIR *dirp)
{
	assert (dirp != NULL);

	if (dirp->search_handle == INVALID_HANDLE_VALUE) {
		/* directory stream was opened/rewound incorrectly or ended normally */
		return NULL;
	}

	/* get next directory entry */
	if (dirp->cached != 0) {
		/* a valid directory entry already in memory */
		dirp->cached = 0;
	} else {
		/* read next directory entry from disk */
		if (FindNextFileA (dirp->search_handle, &dirp->current.data) == FALSE) {
			/* the very last file has been processed or an error occured */
			FindClose (dirp->search_handle);
			dirp->search_handle = INVALID_HANDLE_VALUE;
			return NULL;
		}
	}

	/* copy as a multibyte character string */
	STRNCPY ( dirp->current.d_name,
		dirp->current.data.cFileName,
		sizeof(dirp->current.d_name) );
	dirp->current.d_name[MAX_PATH] = '\0';

	return &dirp->current;
}

/*****************************************************************************
* Close directory stream opened by opendir() function.  Close of the
* directory stream invalidates the DIR structure as well as any previously
* read directory entry.
*/
static int closedir(DIR *dirp)
{
	assert (dirp != NULL);

	/* release search handle */
	if (dirp->search_handle != INVALID_HANDLE_VALUE) {
		FindClose (dirp->search_handle);
		dirp->search_handle = INVALID_HANDLE_VALUE;
	}

	/* release directory handle */
	free (dirp);
	return 0;
}

#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
int getdir(string dir, vector<string> &files);
int main(){
	string dir = string(".");//資料夾路徑(絕對位址or相對位址)
	vector<string> files = vector<string>();
	getdir(dir, files);
	cout << "please input prefix: ";
	string prefix;
	cin >> prefix;
	//輸出資料夾和檔案名稱於螢幕
	for(int i=0; i<files.size(); i++){
		if (files[i].size()>2)
		{
			istringstream iss;
			string origin_name = files[i];
			// find number
			iss.str(origin_name);
			int num = -1;
			char tmp = '.';
			for (int j=0;j<origin_name.size();j++)
			{
				iss >> num;
				if (num < 10)
				{
					iss.str(origin_name.c_str()+j);
					iss.clear();
				}
				else
				{break;}
			}
			// find name ext
			string name;
			string ext;
			int dot = -1;
			for (int j=origin_name.size()-1;j>0;j--)
			{
				if (origin_name[j] == '.')
				{
					dot = j;
					break;
				}
			}
			if (dot > 0)
			{
				name.insert(name.begin(), origin_name.begin(), origin_name.begin()+dot);
				ext.insert(ext.begin(), origin_name.begin()+dot+1, origin_name.end());
				std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				if (ext != "exe")
				{
					ostringstream oss;
					//oss << "heyzo.com_" << setfill('0') << setw(4) << num << "." << ext;
					oss << prefix << name << "." << ext;
					string res;

					int rrr = rename(files[i].c_str(), oss.str().c_str());
				}
			}
			else
			{
				cout << "nodot " << files[i] << endl;
			}
		}
		else
		{
			cout << files[i] << endl;
		}
	}
	system("pause");
	return 0;
}
int getdir(string dir, vector<string> &files){
	DIR *dp;//創立資料夾指標
	struct dirent *dirp;
	if((dp = opendir(dir.c_str())) == NULL){
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}
	while((dirp = readdir(dp)) != NULL){//如果dirent指標非空
		files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
	}
	closedir(dp);//關閉資料夾指標
	return 0;
}
