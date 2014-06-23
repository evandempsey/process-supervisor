int whitelist[338] = {
    0, // 0 - sys_restart_syscall
    1, // 1 - sys_exit
    0, // 2 - sys_fork
    1, // 3 - sys_read
    1, // 4 - sys_write
    1, // 5 - sys_open
    1, // 6 - sys_close
    0, // 7 - sys_waitpid
    0, // 8 - sys_creat
    0, // 9 - sys_link
    0, // 10 - sys_unlink
    0, // 11 - sys_execve
    0, // 12 - sys_chdir
    1, // 13 - sys_time
    0, // 14 - sys_mknod
    0, // 15 - sys_chmod
    0, // 16 - sys_lchown16
    0, // 17 - not implemented
    0, // 18 - sys_stat
    0, // 19 - sys_lseek
    1, // 20 - sys_getpid
    0, // 21 - sys_mount
    0, // 22 - sys_oldumount
    0, // 23 - sys_setuid16
    0, // 24 - sys_getuid16
    0, // 25 - sys_stime
    0, // 26 - sys_ptrace
    0, // 27 - sys_alarm
    0, // 28 - sys_fstat
    0, // 29 - sys_pause
    0, // 30 - sys_utime
    0, // 31 - not implemented
    0, // 32 - not implemented
    1, // 33 - sys_access
    0, // 34 - sys_nice
    0, // 35 - not implemented
    0, // 36 - sys_sync
    0, // 37 - sys_kill
    0, // 38 - sys_rename
    0, // 39 - sys_mkdir
    0, // 40 - sys_rmdir
    0, // 41 - sys_dup
    0, // 42 - sys_pipe
    0, // 43 - sys_times
    0, // 44 - not implemented
    1, // 45 - sys_brk
    0, // 46 - sys_setgid16
    0, // 47 - sys_getgid16
    0, // 48 - sys_signal
    0, // 49 - sys_geteuid16
    0, // 50 - sys_getegid16
    0, // 51 - sys_acct
    0, // 52 - sys_umount
    0, // 53 - not implemented
    1, // 54 - sys_ioctl
    0, // 55 - sys_fcntl
    0, // 56 - not implemented
    0, // 57 - sys_setpgid
    0, // 58 - not implemented
    0, // 59 - sys_olduname
    0, // 60 - sys_umask
    0, // 61 - sys_chroot
    0, // 62 - sys_ustat
    0, // 63 - sys_dup2
    1, // 64 - sys_getppid
    0, // 65 - sys_getpgrp
    0, // 66 - sys_setsid
    1, // 67 - sys_sigaction
    0, // 68 - sys_sgetmask
    0, // 69 - sys_ssetmask
    0, // 70 - sys_setreuid16
    0, // 71 - sys_setregid16
    0, // 72 - sys_sigsuspend
    0, // 73 - sys_sigpending
    0, // 74 - sys_sethostname
    0, // 75 - sys_setrlimit
    0, // 76 - sys_old_getrlimit
    0, // 77 - sys_getrusage
    0, // 78 - sys_gettimeofday
    0, // 79 - sys_settimeofday
    0, // 80 - sys_getgroups16
    0, // 81 - sys_setgroups16
    0, // 82 - sys_old_select
    0, // 83 - sys_symlink
    0, // 84 - sys_lstat
    1, // 85 - sys_readlink
    0, // 86 - sys_uselib
    0, // 87 - sys_swapon
    0, // 88 - sys_reboot
    0, // 89 - sys_old_readdir
    0, // 90 - sys_old_mmap
    1, // 91 - sys_munmap
    0, // 92 - sys_truncate
    0, // 93 - sys_ftruncate
    0, // 94 - sys_fchmod
    0, // 95 - sys_fchown16
    0, // 96 - sys_getpriority
    0, // 97 - sys_setpriority
    0, // 98 - not implemented
    0, // 99 - sys_statfs
    0, // 100 - sys_fstatfs
    0, // 101 - sys_ioperm
    0, // 102 - sys_socketcall
    0, // 103 - sys_syslog
    0, // 104 - sys_setitimer
    0, // 105 - sys_getitimer
    0, // 106 - sys_newstat
    0, // 107 - sys_newlstat
    0, // 108 - sys_newfstat
    0, // 109 - sys_uname
    0, // 110 - sys_iopl
    0, // 111 - sys_vhangup
    0, // 112 - not implemented
    0, // 113 - sys_vm86old
    1, // 114 - sys_wait4
    0, // 115 - sys_swapoff
    0, // 116 - sys_sysinfo
    0, // 117 - sys_ipc
    0, // 118 - sys_fsync
    1, // 119 - sys_sigreturn
    1, // 120 - sys_clone
    0, // 121 - sys_setdomainname
    1, // 122 - sys_newuname
    0, // 123 - sys_modify_ldt
    0, // 124 - sys_adjtimex
    1, // 125 - sys_mprotect
    0, // 126 - sys_sigprocmask
    0, // 127 - not implemented
    0, // 128 - sys_init_module
    0, // 129 - sys_delete_module
    0, // 130 - not implemented
    0, // 131 - sys_quotactl
    0, // 132 - sys_getpgid
    0, // 133 - sys_fchdir
    0, // 134 - sys_bdflush
    0, // 135 - sys_sysfs
    0, // 136 - sys_personality
    0, // 137 - not implemented
    0, // 138 - sys_setfsuid16
    0, // 139 - sys_setfsgid16
    1, // 140 - sys_llseek
    0, // 141 - sys_getdents
    1, // 142 - sys_select
    0, // 143 - sys_flock
    0, // 144 - sys_msync
    0, // 145 - sys_readv
    0, // 146 - sys_writev
    0, // 147 - sys_getsid
    0, // 148 - sys_fdatasync
    0, // 149 - sys_sysctl
    0, // 150 - sys_mlock
    0, // 151 - sys_munlock
    0, // 152 - sys_mlockall
    0, // 153 - sys_munlockall
    0, // 154 - sys_sched_setparam
    0, // 155 - sys_sched_getparam
    0, // 156 - sys_sched_setscheduler
    0, // 157 - sys_sched_getscheduler
    0, // 158 - sys_sched_yield
    0, // 159 - sys_sched_get_priority_max
    0, // 160 - sys_sched_get_priority_min
    0, // 161 - sys_sched_rr_get_interval
    0, // 162 - sys_nanosleep
    0, // 163 - sys_mremap
    0, // 164 - sys_setresuid16
    0, // 165 - sys_getresuid16
    0, // 166 - sys_vm86
    0, // 167 - not implemented
    0, // 168 - sys_poll
    0, // 169 - sys_nfsservctl
    0, // 170 - sys_setresgid16
    0, // 171 - sys_getresgid16
    0, // 172 - sys_prctl
    0, // 173 - sys_rt_sigreturn
    1, // 174 - sys_rt_sigaction
    1, // 175 - sys_rt_sigprocmask
    0, // 176 - sys_rt_sigpending
    0, // 177 - sys_rt_sigtimedwait
    0, // 178 - sys_rt_sigqueueinfo
    0, // 179 - sys_rt_sigsuspend
    0, // 180 - sys_pread64
    0, // 181 - sys_pwrite64
    0, // 182 - sys_chown16
    1, // 183 - sys_getcwd
    0, // 184 - sys_capget
    0, // 185 - sys_capset
    0, // 186 - sys_sigaltstack
    0, // 187 - sys_sendfile
    0, // 188 - not implemented
    0, // 189 - not implemented
    0, // 190 - sys_vfork
    1, // 191 - sys_getrlimit
    1, // 192 - sys_mmap_pgoff
    0, // 193 - sys_truncate64
    0, // 194 - sys_ftruncate64
    1, // 195 - sys_stat64
    1, // 196 - sys_lstat64
    1, // 197 - sys_fstat64
    0, // 198 - sys_lchown
    1, // 199 - sys_getuid
    1, // 200 - sys_getgid
    1, // 201 - sys_geteuid
    1, // 202 - sys_getegid
    0, // 203 - sys_setreuid
    0, // 204 - sys_setregid
    0, // 205 - sys_getgroups
    0, // 206 - sys_setgroups
    0, // 207 - sys_fchown
    0, // 208 - sys_setresuid
    0, // 209 - sys_getresuid
    0, // 210 - sys_setresgid
    0, // 211 - sys_getresgid
    0, // 212 - sys_chown
    0, // 213 - sys_setuid
    0, // 214 - sys_setgid
    0, // 215 - sys_setfsuid
    0, // 216 - sys_setfsgid
    0, // 217 - sys_pivot_root
    0, // 218 - sys_mincore
    0, // 219 - sys_madvise
    1, // 220 - sys_getdents64
    1, // 221 - sys_fcntl64
    0, // 222 - not implemented
    0, // 223 - not implemented
    1, // 224 - sys_gettid
    0, // 225 - sys_readahead
    0, // 226 - sys_setxattr
    0, // 227 - sys_lsetxattr
    0, // 228 - sys_fsetxattr
    1, // 229 - sys_getxattr
    0, // 230 - sys_lgetxattr
    0, // 231 - sys_fgetxattr
    0, // 232 - sys_listxattr
    0, // 233 - sys_llistxattr
    0, // 234 - sys_flistxattr
    0, // 235 - sys_removexattr
    0, // 236 - sys_lremovexattr
    0, // 237 - sys_fremovexattr
    0, // 238 - sys_tkill
    0, // 239 - sys_sendfile64
    1, // 240 - sys_futex
    0, // 241 - sys_sched_setaffinity
    0, // 242 - sys_sched_getaffinity
    1, // 243 - sys_set_thread_area
    0, // 244 - sys_get_thread_area
    0, // 245 - sys_io_setup
    0, // 246 - sys_io_destroy
    0, // 247 - sys_io_getevents
    0, // 248 - sys_io_submit
    0, // 249 - sys_io_cancel
    0, // 250 - sys_fadvise64
    0, // 251 - not implemented
    1, // 252 - sys_exit_group
    0, // 253 - sys_lookup_dcookie
    1, // 254 - sys_epoll_create
    1, // 255 - sys_epoll_ctl
    1, // 256 - sys_epoll_wait
    0, // 257 - sys_remap_file_pages
    1, // 258 - sys_set_tid_address
    0, // 259 - sys_timer_create
    0, // 260 - sys_timer_settime
    0, // 261 - sys_timer_gettime
    0, // 262 - sys_timer_getoverrun
    0, // 263 - sys_timer_delete
    0, // 264 - sys_clock_settime
    1, // 265 - sys_clock_gettime
    1, // 266 - sys_clock_getres
    0, // 267 - sys_clock_nanosleep
    1, // 268 - sys_statfs64
    0, // 269 - sys_fstatfs64
    0, // 270 - sys_tgkill
    0, // 271 - sys_utimes
    0, // 272 - sys_fadvise64_64
    0, // 273 - not implemented
    0, // 274 - sys_mbind
    0, // 275 - sys_get_mempolicy
    0, // 276 - sys_set_mempolicy
    0, // 277 - sys_mq_open
    0, // 278 - sys_mq_unlink
    0, // 279 - sys_mq_timedsend
    0, // 280 - sys_mq_timedreceive
    0, // 281 - sys_mq_notify
    0, // 282 - sys_mq_getsetattr
    0, // 283 - sys_kexec_load
    0, // 284 - sys_waitid
    0, // 285 - not implemented
    0, // 286 - sys_add_key
    0, // 287 - sys_request_key
    0, // 288 - sys_keyctl
    0, // 289 - sys_ioprio_set
    0, // 290 - sys_ioprio_get
    0, // 291 - sys_inotify_init
    0, // 292 - sys_inotify_add_watch
    0, // 293 - sys_inotify_rm_watch
    0, // 294 - sys_migrate_pages
    1, // 295 - sys_openat
    0, // 296 - sys_mkdirat
    0, // 297 - sys_mknodat
    0, // 298 - sys_fchownat
    0, // 299 - sys_futimesat
    0, // 300 - sys_fstatat64
    0, // 301 - sys_unlinkat
    0, // 302 - sys_renameat
    0, // 303 - sys_linkat
    0, // 304 - sys_symlinkat
    0, // 305 - sys_readlinkat
    0, // 306 - sys_fchmodat
    0, // 307 - sys_faccessat
    0, // 308 - sys_pselect6
    0, // 309 - sys_ppoll
    0, // 310 - sys_unshare
    1, // 311 - sys_set_robust_list
    0, // 312 - sys_get_robust_list
    0, // 313 - sys_splice
    0, // 314 - sys_sync_file_range
    0, // 315 - sys_tee
    0, // 316 - sys_vmsplice
    0, // 317 - sys_move_pages
    0, // 318 - sys_getcpu
    0, // 319 - sys_epoll_pwait
    0, // 320 - sys_utimensat
    0, // 321 - sys_signalfd
    0, // 322 - sys_timerfd_create
    0, // 323 - sys_eventfd
    0, // 324 - sys_fallocate
    0, // 325 - sys_timerfd_settime
    0, // 326 - sys_timerfd_gettime
    0, // 327 - sys_signalfd4
    1, // 328 - sys_eventfd2
    1, // 329 - sys_epoll_create1
    0, // 330 - sys_dup3
    1, // 331 - sys_pipe2
    0, // 332 - sys_inotify_init1
    0, // 333 - sys_preadv
    0, // 334 - sys_pwritev
    0, // 335 - sys_rt_tgsigqueueinfo
    0, // 336 - sys_perf_event_open
    0, // 337 - sys_recvmmsg
};
