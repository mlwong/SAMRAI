source ../misc/KeyFrame1.tcl
source ../misc/eng3d_pillers_textured.tcl

vtkLight newlight
newlight SetPosition 0.75 0.5 1
RenderWindow.renderer AddLight newlight
set lights [RenderWindow.renderer GetLights]
$lights InitTraversal
set first_light [$lights GetNextItem]
$first_light SetIntensity 0

if { [string length [info commands \
	vol]] } {
    volInterface SetCroppingRegionPlanes 0 41.88 0 70 0 72
    volInterface SetCropping 1
}

source ../misc/swing1.tcl
KeyRun swing1 72

