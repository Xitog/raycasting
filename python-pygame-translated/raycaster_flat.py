#
# Original CPP code is:
#
# Copyright (c) 2004-2007, Lode Vandevenne
#
# All rights reserved.
#
#-------------------------------------------------------------------------------
#
# Original CPP code license is:
#
#  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#-------------------------------------------------------------------------------
#
# Translation in Python was made by Damien Gouteux in 2017 and is licensed under the terms of previous license.
#

import time
import pygame
from math import cos, sin, sqrt
from pygame.locals import *
from pygame import Surface

mapWidth : int = 24
mapHeight : int = 24

worldMap : [[int]] = [
            [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1],
            [1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1],
            [1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,7,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,7,0,0,0,0,1],
            [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,7,0,0,0,0,1],
            [1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
            [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
    ]

def main():
     # x and y start position
    posX : float = 22
    posY : float = 12
    # initial direction vector
    dirX : float = -1
    dirY  : float = 0
    # the 2d raycaster version of camera plane
    planeX : float = 0
    planeY : float = 0.66
    
    curTime : float = 0 # time of current frame
    oldTime : float = 0 # time of previous frame
    
    pygame.init()
    pygame.display.set_caption('raycaster')
    w = 512
    h = 384
    screen : Surface = pygame.display.set_mode((w, h), pygame.DOUBLEBUF, 32)
    
    up : bool = False
    down : bool = False
    right : bool = False
    left : bool = False
    done : bool = False
    while not done:
        for x in range(0, w):
            # calculate ray position and direction 
            cameraX : float = 2 * x / float(w) - 1; # x-coordinate in camera space
            rayPosX : float = posX
            rayPosY : float = posY
            rayDirX : float = dirX + planeX * cameraX
            rayDirY : float = dirY + planeY * cameraX
            
            # which box of the map we're in  
            mapX : int = int(rayPosX)
            mapY : int = int(rayPosY)
            
            # length of ray from current position to next x or y-side
            sideDistX : float = 0.0
            sideDistY : float = 0.0
            
            # Added by me
            if rayDirX == 0: rayDirX = 0.00001
            if rayDirY == 0: rayDirY = 0.00001
            
            # length of ray from one x or y-side to next x or y-side
            deltaDistX : float = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
            deltaDistY : float = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
            perpWallDist : float = 0.0
            
            # what direction to step in x or y-direction (either +1 or -1)
            stepX : int = 0
            stepY : int = 0
            
            # was there a wall hit?
            hit : bool = False 
            side :int = 0 # was a NS or a EW wall hit?
            
            # calculate step and initial sideDist
            if rayDirX < 0:
                stepX = -1
                sideDistX = (rayPosX - mapX) * deltaDistX
            else:
                stepX = 1
                sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX
            if rayDirY < 0:
                stepY = -1
                sideDistY = (rayPosY - mapY) * deltaDistY
            else:
                stepY = 1
                sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY
            
            # perform DDA
            while not hit:
                # jump to next map square, OR in x-direction, OR in y-direction
                if sideDistX < sideDistY:
                    sideDistX += deltaDistX
                    mapX += stepX
                    side = 0
                else:
                    sideDistY += deltaDistY
                    mapY += stepY
                    side = 1
                
                # Check if ray has hit a wall
                if worldMap[mapX][mapY] > 0:
                     hit = True
            
            # Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
            if side == 0:
                perpWallDist = abs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX)
            else:
                perpWallDist = abs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY)
            
            # Calculate height of line to draw on screen
            lineHeight : int = abs(int(h / perpWallDist))
            
            # calculate lowest and highest pixel to fill in current stripe
            drawStart : int = -lineHeight / 2 + h / 2
            if drawStart < 0:
                drawStart = 0
            drawEnd : int = lineHeight / 2 + h / 2
            if drawEnd >= h:
                drawEnd = h - 1
            
            # choose wall color
            color : (int, int, int) = None
            if worldMap[mapX][mapY] == 1:
                color = (255, 0, 0) # red
            elif worldMap[mapX][mapY] == 2:
                color = (0, 255, 0) # green
            elif worldMap[mapX][mapY] == 3:
                color = (0, 0, 255) # blue
            elif worldMap[mapX][mapY] == 4:
                color = (255, 255, 255) # white
            elif worldMap[mapX][mapY] == 5:
                color = (255, 255, 0) # yellow
            elif worldMap[mapX][mapY] == 6:
                color = (0, 255, 255) # ?
            elif worldMap[mapX][mapY] == 7:
                color = (255, 0, 255) # ?
            else:
                raise Exception("Color not found!")
            
            # give x and y sides different brightness
            if side == 1:
                color = (color[0] / 2, color[1] / 2, color[2] / 2)
            
            # draw the pixels of the stripe as a vertical line
            pygame.draw.line(screen, color, (x, drawStart), (x, drawEnd), 1)
            
            
        # timing for input and FPS counter
        oldTime = curTime
        curTime = time.time()
        frameTime : float = (curTime - oldTime) # frameTime is the time this frame has taken, in seconds
        # print(1.0 / frameTime) # FPS counter
        
        pygame.display.flip()
        screen.fill((0,0,0))
        
        # speed modifiers
        moveSpeed : float = frameTime * 5.0 # the constant value is in squares/second
        rotSpeed : float = frameTime * 3.0 # the constant value is in radians/second
        
        for event in pygame.event.get():
            if event.type == QUIT:
                done = True
            elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    done = True
                if event.key == K_RIGHT:
                    right = True
                if event.key == K_LEFT:
                    left = True
                if event.key == K_UP:
                    up = True
                if event.key == K_DOWN:
                    down = True
            elif event.type == KEYUP:
                if event.key == K_RIGHT:
                    right = False
                if event.key == K_LEFT:
                    left = False
                if event.key == K_UP:
                    up = False
                if event.key == K_DOWN:
                    down = False
        
        # move forward if no wall in front of you
        if up:
            if worldMap[int(posX + dirX * moveSpeed)][int(posY)] == False:
                posX += dirX * moveSpeed
            if worldMap[int(posX)][int(posY + dirY * moveSpeed)] == False:
                posY += dirY * moveSpeed
        # move backwards if no wall behind you
        if down:
            if worldMap[int(posX - dirX * moveSpeed)][int(posY)] == False:
                posX -= dirX * moveSpeed
            if worldMap[int(posX)][int(posY - dirY * moveSpeed)] == False:
                posY -= dirY * moveSpeed
        # rotate to the right
        if right:
            # both camera direction and camera plane must be rotated
            oldDirX : float = dirX
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed)
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed)
            oldPlaneX : float = planeX
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed)
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed)
        # rotate to the left
        if left:
            # both camera direction and camera plane must be rotated
            oldDirX : float = dirX
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed)
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed)
            oldPlaneX : float = planeX
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed)
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed)

if __name__ == '__main__':
    main()
    pygame.quit()
