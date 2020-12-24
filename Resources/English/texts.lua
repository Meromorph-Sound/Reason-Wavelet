format_version = "1.0"

texts = {
  ["audioOutputL"] = "Audio Output",
  ["audioOutputR"] = "Audio Output",
  ["audioInputL"] = "Audio Input",
  ["audioInputR"] = "Audio Input",
  
  ["propertyname_Approximation"] = "Approximation",
  ["propertyname_Algorithm"] = "Algorithm",
  ["propertyname_AlgorithmDisplay"] = "Algorithm",
  ["threshold"] = "threshold",
  ["scale"] = "scale",
  
  ["short_Approximation"] = "APRX",
  ["shortest_Approximation"] = "APRX",
  ["short_Algorithm"] = "ALG",
  ["shortest_Algorithm"] = "ALG",
  ["short_Threshold"] = "THR",
  ["shortest_Threshold"] = "THR",
}
for n = 1,4 do
    texts["short_Detail"..n] = "D"..n
    texts["shortest_Detail"..n] = "D"..n
    texts["propertyname_Detail"..n] = "Detail "..n
end