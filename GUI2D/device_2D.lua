format_version = "2.0"



front = {
  Bg = { {path = "front1U"} },
  onoffbypass = {
      offset = {185,50},
      {path="Fader_Bypass_3frames", frames = 3 },
    },
  deviceName = {
    offset = { 3200, 250},
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  detail1 = {
    offset = { 1100, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  detail2 = {
    offset = { 1400, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  detail3 = {
    offset = { 1700, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  detail4 = {
    offset = { 2000, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  approximation = {
    offset = { 2300, 80 },
    { path = "Knob_01_63frames", frames = 63 }
  },
  algorithm = {
    offset = { 2650, 100 },
    { path = "Button_23_2frames", frames = 2 }
    },
   algorithmDisplay = {
    offset = { 2850, 130 },
    { path = "Lamp_18_2frames", frames = 2 }
  }
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
	Bg = {{ path = "Panel_Folded_Front" }}
}
folded_back = { 
  Bg = {{ path = "Panel_Folded_Back" }},
  CableOrigin = { offset = { 1885, 75 }}
}





