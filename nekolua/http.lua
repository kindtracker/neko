local Lunar = require("lunar")
local JSONService = Lunar:GetService("JSONService")

local Http = {}

local CompiledHttpRequest = Neko:LoadString([=[
  const Response = await fetch(Arguments[0], JSON.parse(Arguments[1]))

  return await Response.text()
]=])

function Http:Request(Url, Options)
	local Response = CompiledHttpRequest(Url, JSONService:Encode(Options))
	return JSONService:Decode(Response)
end

function Http:InitPlugin()
	Neko.Http = Http
end

return Http
