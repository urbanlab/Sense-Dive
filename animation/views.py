from django.shortcuts import render, get_object_or_404

from django.http import HttpResponse
from django.template import loader

from .models import Animation

# Create your views here.

def home(request):
	objs = Animation.objects.filter(status='p')
	context = {
    	    'animation_list': objs,
    	}
	return render(request, 'index.html', context)