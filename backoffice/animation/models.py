from django.db import models
from datetime import datetime

from django.db import models
from django.conf import settings
from django.utils.safestring import mark_safe
from django.core.exceptions import ValidationError
from django.core.validators import FileExtensionValidator

# Create your models here.

STATUS_CHOICES = (
    ('p', 'Published'),
    ('w', 'Withdrawn'),
)

class GroupBus(models.Model):
    name = models.CharField(max_length=200)
    status = models.CharField(max_length=1, choices=STATUS_CHOICES, default='p')
    animation = models.ForeignKey('Animation', related_name='Animation', null=True)

    def status_tag(self):
        if self.status is 'p':
            return mark_safe('<div style="width:30px; height:30px; background:#09f438; border-radius:15px"></div>')
        elif self.status is 'w':
            return mark_safe('<div style="width:30px; height:30px; background:#ff1000; border-radius:15px"></div>')
    status_tag.short_description = 'Status'

    def __str__(self):
        return self.name

class Bus(models.Model):
    ligne = models.CharField(max_length=100)
    group = models.ForeignKey(GroupBus, related_name='Groupe', null=True)
    status = models.CharField(max_length=1, choices=STATUS_CHOICES, default='p')

    def status_tag(self):
        if self.status is 'p':
            return mark_safe('<div style="width:30px; height:30px; background:#09f438; border-radius:15px"></div>')
        elif self.status is 'w':
            return mark_safe('<div style="width:30px; height:30px; background:#ff1000; border-radius:15px"></div>')
    status_tag.short_description = 'Status'

    def __str__(self):
        return self.ligne

def upload_directory_path_media(instance, filename):
    return 'uploads/media/{0}/{1}'.format(instance.name, filename)

class Media(models.Model):
    name = models.CharField(max_length=100)
    file = models.FileField(upload_to=upload_directory_path_media)

    def __str__(self):
        return self.name

def upload_directory_path_binary(instance, filename):
    return 'uploads/sources/{0}/{1}'.format(instance.name, filename)

class Binary(models.Model):
    name = models.CharField(max_length=100)
    file = models.FileField(upload_to=upload_directory_path_binary)

    def __str__(self):
        return self.name

def upload_directory_path(instance, filename):
        return 'uploads/Animation/{0}'.format(filename)

class Animation(models.Model):
    title = models.CharField(max_length=200)
    binary = models.ForeignKey(Binary, null=True)
    medias = models.ManyToManyField(Media)
    pub_date = models.DateField(default=datetime.now, blank=True)
    status = models.CharField(max_length=1, choices=STATUS_CHOICES, default='p')

    def __str__(self):
        return self.title

    def status_tag(self):
        if self.status is 'p':
            return mark_safe('<div style="width:30px; height:30px; background:#09f438; border-radius:15px"></div>')
        elif self.status is 'w':
            return mark_safe('<div style="width:30px; height:30px; background:#ff1000; border-radius:15px"></div>')
        
    status_tag.short_description = 'Status'