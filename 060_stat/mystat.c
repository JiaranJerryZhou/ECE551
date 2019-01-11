#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

//get the file type by st_mode
const char * getFileType(struct stat * mystat) {
  const char * fileMode = NULL;
  switch (mystat->st_mode & S_IFMT) {
    case S_IFBLK: {
      fileMode = "block special file";
      break;
    }
    case S_IFCHR: {
      fileMode = "character special file";
      break;
    }
    case S_IFDIR: {
      fileMode = "directory";
      break;
    }
    case S_IFIFO: {
      fileMode = "fifo";
      break;
    }
    case S_IFLNK: {
      fileMode = "symbolic link";
      break;
    }
    case S_IFREG: {
      fileMode = "regular file";
      break;
    }
    case S_IFSOCK: {
      fileMode = "socket";
      break;
    }
    default: {
      fileMode = "unknown?";
      break;
    }
  }
  return fileMode;
}

//this function get the human readable description and return it in 10 characters
char * getDescription(struct stat * mystat) {
  char * des = malloc(11 * sizeof(*des));
  switch (mystat->st_mode & S_IFMT) {
    case S_IFBLK: {
      des[0] = 'b';
      break;
    }
    case S_IFCHR: {
      des[0] = 'c';
      break;
    }
    case S_IFDIR: {
      des[0] = 'd';
      break;
    }
    case S_IFIFO: {
      des[0] = 'p';
      break;
    }
    case S_IFLNK: {
      des[0] = 'l';
      break;
    }
    case S_IFREG: {
      des[0] = '-';
      break;
    }
    case S_IFSOCK: {
      des[0] = 's';
      break;
    }
    default: { break; }
  }
  //check the second bit
  if ((mystat->st_mode & S_IRUSR) != 0) {
    des[1] = 'r';
  }
  else {
    des[1] = '-';
  }
  //check the third bit
  if ((mystat->st_mode & S_IWUSR) != 0) {
    des[2] = 'w';
  }
  else {
    des[2] = '-';
  }
  //check the fourth bit
  if ((mystat->st_mode & S_IXUSR) != 0) {
    des[3] = 'x';
  }
  else {
    des[3] = '-';
  }
  //fifth bit
  if ((mystat->st_mode & S_IRGRP) != 0) {
    des[4] = 'r';
  }
  else {
    des[4] = '-';
  }
  //sixth bit
  if ((mystat->st_mode & S_IWGRP) != 0) {
    des[5] = 'w';
  }
  else {
    des[5] = '-';
  }
  //seventh bit
  if ((mystat->st_mode & S_IXGRP) != 0) {
    des[6] = 'x';
  }
  else {
    des[6] = '-';
  }
  //eighth bit
  if ((mystat->st_mode & S_IROTH) != 0) {
    des[7] = 'r';
  }
  else {
    des[7] = '-';
  }
  //nineth bit
  if ((mystat->st_mode & S_IWOTH) != 0) {
    des[8] = 'w';
  }
  else {
    des[8] = '-';
  }
  //tenth bit
  if ((mystat->st_mode & S_IXOTH) != 0) {
    des[9] = 'x';
  }
  else {
    des[9] = '-';
  }
  des[10] = '\0';
  return des;
}
int main(int argc, char ** argv) {
  struct stat mystat;
  //not enough argument
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; i++) {
    //lstat returns error
    if (lstat(argv[i], &mystat) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }

    const char * fileMode = getFileType(&mystat);
    //check if it is a link
    if ((mystat.st_mode & S_IFMT) == S_IFLNK) {
      char linktarget[256];
      ssize_t len = readlink(argv[i], linktarget, 256);
      linktarget[len] = '\0';
      printf("  File: %s -> %s\n", argv[i], linktarget);
    }
    else {
      printf("  File: %s\n", argv[i]);
    }
    printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
           mystat.st_size,
           mystat.st_blocks,
           mystat.st_blksize,
           fileMode);
    //check if it is a device
    if ((mystat.st_mode & S_IFMT) == S_IFCHR || (mystat.st_mode & S_IFMT) == S_IFBLK) {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %x,%x\n",
             mystat.st_dev,
             mystat.st_dev,
             mystat.st_ino,
             mystat.st_nlink,
             major(mystat.st_rdev),
             minor(mystat.st_rdev));
    }
    else {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
             mystat.st_dev,
             mystat.st_dev,
             mystat.st_ino,
             mystat.st_nlink);
    }
    //permission is all the bits of st_mode except the ones for the file type
    mode_t permission = mystat.st_mode & ~S_IFMT;
    char * humanReadable = getDescription(&mystat);
    //get the information for user and group
    struct passwd * User = getpwuid(mystat.st_uid);
    struct group * Group = getgrgid(mystat.st_gid);
    printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
           permission,
           humanReadable,
           mystat.st_uid,
           User->pw_name,
           mystat.st_gid,
           Group->gr_name);
    free(humanReadable);
    char * a_timestr = time2str(&mystat.st_atime, mystat.st_atim.tv_nsec);
    char * m_timestr = time2str(&mystat.st_mtime, mystat.st_mtim.tv_nsec);
    char * c_timestr = time2str(&mystat.st_ctime, mystat.st_ctim.tv_nsec);
    printf("Access: %s\n", a_timestr);
    printf("Modify: %s\n", m_timestr);
    printf("Change: %s\n", c_timestr);
    free(a_timestr);
    free(m_timestr);
    free(c_timestr);
    printf(" Birth: -\n");
  }
  return EXIT_SUCCESS;
}
