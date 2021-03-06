m = nuke.menu('Nodes').addMenu('Hydra')

m.addCommand('Lights/HydraCylinderLight', 'nuke.createNode("HydraCylinderLight")')
m.addCommand('Lights/HydraDiskLight', 'nuke.createNode("HydraDiskLight")')
m.addCommand('Lights/HydraDomeLight', 'nuke.createNode("HydraDomeLight")')
m.addCommand('Lights/HydraRectLight', 'nuke.createNode("HydraRectLight")')
m.addCommand('Lights/HydraSphereLight', 'nuke.createNode("HydraSphereLight")')
m.addCommand('HydraRender', 'nuke.createNode("HydraRender")')
m.addCommand('HydraScene', 'nuke.createNode("HydraScene")')
