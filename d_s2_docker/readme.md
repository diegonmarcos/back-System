# DOCKER

## Install
sudo apt update
sudo apt install docker.io

## Start Service: Start the Docker service:
sudo systemctl start docker
sudo systemctl status docker

## Sudo: This allows you to run Docker commands without using sudo.
sudo usermod -aG docker $USER