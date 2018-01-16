from django.contrib import admin

from .models import Animation, Bus, GroupBus


# Register your models here.

def make_published(modeladmin, request, queryset):
    queryset.update(status='p')
    rows_updated = queryset.update(status='p')
    if rows_updated == 1:
        message_bit = "1 story was"
    else:
        message_bit = "%s stories were" % rows_updated
    self.message_user(request, "%s successfully marked as published." % message_bit)


make_published.short_description = "Publier les animations séléctionnées"


class AnimationAdmin(admin.ModelAdmin):
    list_display = ['title', 'image_tag', 'status_tag']
    readonly_fields = ['image_tag', 'status_tag']
    ordering = ['pub_date']
    actions = [make_published]
    exclude = ['pub_date']

admin.site.register(Animation, AnimationAdmin)

class BusAdmin(admin.ModelAdmin):
    list_display = ['ligne', 'group', 'status_tag']
    actions = [make_published]

admin.site.register(Bus, BusAdmin)
class GroupBusAdmin(admin.ModelAdmin):
    list_display = ['name', 'animation', 'status_tag']
    actions = [make_published]

admin.site.register(GroupBus, GroupBusAdmin)
