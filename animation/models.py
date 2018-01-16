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


def upload_directory_path(instance, filename):
    return 'uploads/Animation/{1}'.format(filename)


class Animation(models.Model):
    title = models.CharField(max_length=200)
    picture = models.FileField(upload_to=upload_directory_path, validators=[FileExtensionValidator(allowed_extensions=['hap'])])
    pub_date = models.DateField(default=datetime.now, blank=True)
    status = models.CharField(max_length=1, choices=STATUS_CHOICES, default='p')

    def __str__(self):
        return self.title

    def image_tag(self):
        return mark_safe('<img src="{}" width="100px" height="100px" />'.format("/" + self.picture.url))

    image_tag.short_description = 'Image'

    def status_tag(self):
        if self.status is 'p':
            return mark_safe('<div style="width:30px; height:30px; background:#09f438; border-radius:15px"></div>')
        elif self.status is 'w':
            return mark_safe('<div style="width:30px; height:30px; background:#ff1000; border-radius:15px"></div>')
    status_tag.short_description = 'Status'

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
    type = models.CharField(max_length=100)
    secteur = models.CharField(max_length=200)
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