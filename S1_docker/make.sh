# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 12:30:02 by dinepomu          #+#    #+#              #
#    Updated: 2025/03/02 13:06:42 by dinepomu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

######**BUILD AND RUN THE IMAGE**######
### Build the docker image
docker build -t push_swap_image .

### Run the docker image
#docker run push_swap_image
docker run -it
	-v /push_swap:/push_swap
	push_swap_image
	bash

######**INTERACTION INSIDE OF IT**######
### Run the push_swap program (as with -it flag we are inside the container)
#docker run push_swap_image
make "$@"