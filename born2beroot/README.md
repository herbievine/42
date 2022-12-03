# Born2beroot Handbook

### Firewall

###### Check that the UFW service is started

```bash
sudo systemctl status ufw
```

###### Check the open ports 

```bash
sudo ufw status numbered
```

###### SSH

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
