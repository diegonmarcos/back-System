# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 13:07:08 by dinepomu          #+#    #+#              #
#    Updated: 2025/03/02 13:07:54 by dinepomu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Use an Ubuntu base image (or another suitable image for 42 projects)
FROM ubuntu:latest

### Install Python, pip (for pipx) and pipx
RUN apt update && apt install -y python3 python3-pip && rm -rf /var/lib/apt/lists/*
RUN pip3 install pipx && pipx ensurepath

### Copy the list.txt file into the container and # Install necessary system packages
COPY r_apt.txt /tmp/r_apt.txt
COPY r_pipx.txt /tmp/r_apt-get.txt
RUN apt update \
	&& xargs -r apt install -y < /tmp/r_apt.txt \
	&& rm -rf /var/lib/apt/lists/*
RUN \
	&& xargs -r pipx install -y < /tmp/r_pipx.txt \
	&& rm -rf /var/lib/apt/lists/*

### Folder source code
#RUN git clone <GIT_REPO_URL> /push_swap
#COPY push_swap /push_swap
#RUN from mounted mirroed volume done in the docker-compose file

### Set the working directory
WORKDIR /push_swap