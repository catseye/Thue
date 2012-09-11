#!/usr/bin/env ruby

# An implementation of Thue in Ruby.
# Sept 10 2012, Chris Pressey, Cat's Eye Technologies.
# This program is in the public domain.

rules = []
state = 'rules'
body = ''
debug = false
if ARGV[0] == '-d' then
  debug = true
  ARGV.shift
end
File.open(ARGV[0], "r") do |infile|
  while (line = infile.gets)
    line.chomp!
    if state == 'rules' then
      match = line.match /^(.*?)::=(.*?)$/
      if match then
        if match[1] =~ /^\s*$/ then
          state = 'body'
        else
          rules.push({'lhs'=>match[1],'rhs'=>match[2]})
        end
      end
    else
      body += line
    end
  end
end

while true
  if debug then
    puts body
  end
  cands = []
  rules.each do |rule|
    start = 0
    while (pos = body.index(rule['lhs'], start))
      cands.push({'repl'=>rule['rhs'],'pos'=>pos,'len'=>rule['lhs'].length})
      start = pos + 1
    end
  end
  if (l = cands.length) == 0 then
    break
  end
  pick = cands[rand(l)]
  pos = pick['pos']
  len = pick['len']
  repl = pick['repl']
  if repl == ':::' then
    repl = STDIN.gets
    repl.chomp!
  elsif repl =~ /^\~/ then
    if repl.length == 1 then
      puts ""
    else
      print repl[1..-1]
    end
    repl = ""
  end
  if pos == 0 then
    front = ''
  else
    front = body[0..pos-1]
  end
  back = body[pos+len..-1]
  body = front + repl + back
end
