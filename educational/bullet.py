import pygame
import math

class bullet(object):
    """the bullet class"""
    def __init__(self, x, y, ang):
        #pygame.sprite.Sprite.__init__(self) #call Sprite initializer
        self.image = pygame.image.load("img/ball.png")
        self.rect = self.image.get_rect()
        #spawn bullet where space guy fired it from
        self.rect.move_ip(x, y)
        self.angle = ang
        self.xvel = 70
        self.yvel = 70

    def update(self, FrameRate):
        """updates bullet"""
        #FrameRate = FrameRate/100 #framerate should already be in right format by the time we pass here
        return self.move(FrameRate)
        
    def move(self, FrameRate):
        """moves bullet along its trajectory"""
        self.rect.move_ip(self.xvel*math.cos(self.angle)*FrameRate, -self.yvel*math.sin(self.angle)*FrameRate)
        if self.rect.left < 0:
            return False
        elif self.rect.right > 600:
            return False
        elif self.rect.top < 0:
            return False
        return True

    def draw(self, screen):
        """draws the bullet"""
        screen.blit(self.image, self.rect)