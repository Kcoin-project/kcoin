Sample init scripts and service configuration for kcoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/kcoind.service:    systemd service unit configuration
    contrib/init/kcoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/kcoind.openrcconf: OpenRC conf.d file
    contrib/init/kcoind.conf:       Upstart service configuration file
    contrib/init/kcoind.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three startup configurations assume the existence of a "kcoin" user
and group.  They must be created before attempting to use these scripts.

2. Configuration
---------------------------------

At a bare minimum, kcoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, kcoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that kcoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If kcoind is run with "-daemon" flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr.  You can also
generate one from the shell yourself like this:

bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'

Once you have a password in hand, set rpcpassword= in /etc/kcoin/kcoin.conf

For an example configuration file that describes the configuration settings, 
see contrib/debian/examples/kcoin.conf.

3. Paths
---------------------------------

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/kcoind
Configuration file:  /etc/kcoin/kcoin.conf
Data directory:      /var/lib/kcoind
PID file:            /var/run/kcoind/kcoind.pid (OpenRC and Upstart)
                     /var/lib/kcoind/kcoind.pid (systemd)
Lock file:           /var/lock/subsys/kcoind (CentOS)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the kcoin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
kcoin user and group.  Access to kcoin-cli and other kcoind rpc clients
can then be controlled by group membership.

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
"systemctl daemon-reload" in order to update running systemd configuration.

To test, run "systemctl start kcoind" and to enable for system startup run
"systemctl enable kcoind"

4b) OpenRC

Rename kcoind.openrc to kcoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
"/etc/init.d/kcoind start" and configure it to run on startup with
"rc-update add kcoind"

4c) Upstart (for Debian/Ubuntu based distributions)

Drop kcoind.conf in /etc/init.  Test by running "service kcoind start"
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy kcoind.init to /etc/init.d/kcoind. Test by running "service kcoind start".

Using this script, you can adjust the path and flags to the kcoind program by 
setting the KCOIND and FLAGS environment variables in the file 
/etc/sysconfig/kcoind. You can also use the DAEMONOPTS environment variable here.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.


