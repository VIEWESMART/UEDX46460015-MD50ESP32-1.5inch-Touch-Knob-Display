#!/usr/bin/env python3

import sys
import os
import shlex
import importlib
import re
import example_list as ex

_sp = importlib.import_module('subprocess')

langs = ['en']

# Change to script directory for consistency
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

def cmd(s, cwd=None):
  print("")
  print(s)
  print("-------------------------------------")
  r = _sp.run(shlex.split(s), cwd=cwd).returncode
  if r != 0:
    print("Exit build due to previous error")
    exit(-1)

# Get the current branch name
_res = _sp.run(['git', 'branch'], capture_output=True, text=True)
br = next((l for l in _res.stdout.splitlines() if l.startswith('* ')), '')
_res = _sp.run(['git', 'rev-parse', 'HEAD'], capture_output=True, text=True)
gitcommit = _res.stdout.strip()
br = re.sub('\* ', '', br)

# Generate the list of examples
ex.exec()

urlpath = re.sub('release/', '', br)

os.environ['LVGL_URLPATH'] = urlpath
os.environ['LVGL_GITCOMMIT'] = gitcommit

clean = 0
trans = 0
skip_latex = False
args = sys.argv[1:]
if len(args) >= 1:
  if "clean" in args: clean = 1
  if "skip_latex" in args: skip_latex = True

lang = "en"
print("")
print("****************")
print("Building")
print("****************")
if clean:
  cmd("rm -rf " + lang)
  cmd("mkdir " + lang)


print("Running doxygen")
cmd("doxygen Doxyfile", cwd="../scripts")
# BUILD PDF

if not skip_latex:
  # Silly workaround to include the more or less correct PDF download link in the PDF
  #cmd("cp -f " + lang +"/latex/LVGL.pdf LVGL.pdf | true")
  cmd("sphinx-build -b latex . out_latex")

  # Generate PDF
  cmd("latexmk -pdf LVGL.tex", cwd="out_latex")
  # Copy the result PDF to the main directory to make it available for the HTML build
  cmd("cp -f LVGL.pdf ../LVGL.pdf", cwd="out_latex")
else:
  print("skipping latex build as requested")

# BUILD HTML
cmd("sphinx-build -b html . ../out_html")

