# Born2beroot Handbook

### Groups & Users

###### Check groups

Format can be read like so: `<group>:<password>:<id>:<users>`

```bash
getent group <?group>
```

###### Add a new user

```bash
sudo adduser <username>
```

###### Add user to a group

```bash
sudo adduser <username> <group>
```

### Password Policy

###### Check the password prerequisites

```bash
sudo vi /etc/pam.d/common-password
```

###### Check the password expiry

```bash
sudo vi /etc/login.defs
```

###### Check if password policy is applied

```bash
chage -l <username>
```

### Firewall

###### Check that the UFW service has started

```bash
sudo systemctl status ufw
```

###### Check the open ports

```bash
sudo ufw status numbered
```

### SSH

###### Check that the SSH service has started

```bash
sudo systemctl status ssh
```

###### Connect to via SSH

```bash
sudo ssh <username>@127.0.0.1 -p 4242
```

### Other

###### Check the chosen operating system

```bash
cat /etc/os-release
```

###### Check the OS hostname

```bash
hostname
```
