# -*- coding: utf-8 -*-
# Generated by Django 1.11.6 on 2018-01-16 16:08
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('animation', '0002_bus_groupbus'),
    ]

    operations = [
        migrations.AddField(
            model_name='bus',
            name='group',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, related_name='Groupe', to='animation.GroupBus'),
        ),
        migrations.AddField(
            model_name='groupbus',
            name='animation',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, related_name='Animation', to='animation.Animation'),
        ),
    ]