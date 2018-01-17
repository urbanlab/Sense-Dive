import os
import zipfile
from io import BytesIO

from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse
from django.template import loader
from django.http import HttpResponse, Http404

from .models import Animation, Bus


# Create your views here.

def home(request):
    objs = Animation.objects.filter(status='p')
    buss = Bus.objects.filter(status='p')

    context = {
        'animation_list': objs,
        'bus_list': buss
    }
    return render(request, 'index.html', context)


def get_zip(request, name):
    animation = get_object_or_404(Animation, title=name)
    tabs = []
    tabs.append(animation.binary.file.url)
    for t in animation.medias.all():
        tabs.append(t.file.url)

    zip_subdir = "animation" + name
    zip_filename = "%s.zip" % zip_subdir

    s = BytesIO()

    zf = zipfile.ZipFile(s, "w")
    for fpath in tabs:
        fdir, fname = os.path.split(fpath)
        zip_path = os.path.join(zip_subdir, fname)
        print(fpath)
        zf.write(fpath, zip_path)

    zf.close()
    resp = HttpResponse(s.getvalue(), content_type="application/x-zip-compressed")
    resp['Content-Disposition'] = 'attachment; filename=%s' % zip_filename
    return resp
