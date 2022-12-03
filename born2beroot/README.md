# Born2beroot Handbook

### Groups & Users

###### Check all the users

Format can be read like so: `<group>:<password>:<id>:<users>`

```bash
getent group <group>
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

### Firewall

###### Check that the UFW service is started

```bash
sudo systemctl status ufw
```

###### Check the open ports 

```bash
sudo ufw status numbered
```

### SSH

###### Check that the SSH service is started

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
