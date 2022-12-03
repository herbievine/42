# Born2beroot Handbook

## Groups & Users

> Group format can be read like so: `<group>:<password>:<id>:<users>`

#### Check groups

```bash
getent group <?group>
```

#### Check users

```bash
cut -d: -f1 /etc/passwd
```

#### Add a new user

```bash
sudo adduser <username>
```

#### Add a new group

```bash
sudo addgroup <newgroup>
```

#### Add user to a group

```bash
sudo adduser <username> <group>
```

## Password Policy

#### Check the password prerequisites

```bash
sudo vi /etc/pam.d/common-password
```

#### Check the password expiry

```bash
sudo vi /etc/login.defs
```

#### Check if password policy is applied

```bash
chage -l <username>
```

## Sudo

#### Check sudoers

```bash
sudo visudo
```

## Firewall

#### Check that the UFW service has started

```bash
sudo systemctl status ufw
```

#### Check the open ports

```bash
sudo ufw status numbered
```

## SSH

#### Check that the SSH service has started

```bash
sudo systemctl status ssh
```

#### Connect to via SSH

```bash
sudo ssh <username>@127.0.0.1 -p 4242
```

## FTP (Bonus)

> Ports 20 and 21 and enabled due to this protocol

#### Check that the FTP service has started

```bash
sudo systemctl status vsftpd
```

## Other

#### Check the chosen operating system

```bash
cat /etc/os-release
```

#### Check the OS hostname

```bash
hostname
```

#### Check the running CRON jobs

```bash
sudo crontab -l
```
