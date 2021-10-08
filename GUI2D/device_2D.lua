format_version = "2.0"



front = {
  Bg = { {path = "front1U"} },
  onoffbypass = {offset = {200,20},{path="Fader_Bypass_3frames", frames = 3 }},
  deviceName = {offset = { 1900, 10 },{ path = "Tape_Horizontal_1frames", frames = 1 }},
  patches = { offset = { 500,10},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {805,10},{ path = "PatchName_1frames",frames=1}},
  detail1 = {offset = { 1000, 125 },{ path = "Knob_01_63frames", frames = 63 }},
  detail2 = {offset = { 1300, 125 },{ path = "Knob_01_63frames", frames = 63 }},
  detail3 = {offset = { 1600, 125 },{ path = "Knob_01_63frames", frames = 63 }},
  detail4 = {offset = { 1900, 125 },{ path = "Knob_01_63frames", frames = 63 }},
  approximation = {offset = { 2200, 125 },{ path = "Knob_01_63frames", frames = 63 }},
  algorithm = {offset = { 2800, 125 },{ path = "Button_23_2frames", frames = 2 }},
  algorithmDisplay = {offset = { 3000, 155 },{ path = "Lamp_18_2frames-reframed", frames = 2 }}
}
back = {
  Bg = { {path = "backPanel"} },
  Placeholder = {
    offset = { 2000, 100 },
    { path = "Placeholder" },
  },
  deviceName = {
    offset = { 100, 230 },
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  audioInL = {
    offset = { 1000,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
    audioInR = {
    offset = { 1200,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
  audioOutL = {
    offset = { 1550,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
  
  audioOutR = {
    offset = { 1750,120  },
    { path = "SharedAudioJack", frames = 3 }
  },
}




folded_front = {
	Bg = {{ path = "Panel_Folded_Front" }},
  patches = { offset = { 700,24},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {1005,24},{ path = "PatchName_1frames",frames=1}},
  deviceName = { offset = { 2800, 42}, { path = "Tape_Horizontal_1frames", frames = 1 }},
}
folded_back = { 
  Bg = {{ path = "Panel_Folded_Back" }},
  CableOrigin = { offset = { 1885, 75 }}
}





