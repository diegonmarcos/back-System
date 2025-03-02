# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 12:30:02 by dinepomu          #+#    #+#              #
#    Updated: 2025/03/02 17:19:59 by dinepomu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

######**BUILD AND RUN THE IMAGE**######
### Build the docker image
#export DOCKER_BUILDKIT=1
docker build -t push_swap_d . && \
\
### Run the docker image
#docker run push_swap_image
docker run -it \
	-v "$PWD/../../2.CODE:/push_swap" \
	-v /home/diego/Documents/Git/mylib/:/mylib \
	-e PATH="$PATH:$HOME/.local/bin" \
	push_swap_d \
	bash

######**INTERACTION INSIDE OF IT**######
### Run the push_swap program (as with -it flag we are inside the container)
#docker run push_swap_image
#make "$@"