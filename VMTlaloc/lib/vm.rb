class VirtualMachine
  
  def initialize(input_file)
    file = File.new(input_file, "r")
    @procedures = []
    @quadruples = []
    @test = 1
    
    while(line = file.gets || file.gets == "END")
      @quadruples << line.to_s
    end
    
    file.close
  end
  
  def launch!
    @quadruples.each do |quadruple|
      operator, first_oper, second_oper, result = quadruple.chomp.split(" ")

      case operator.to_i
        when 213 # print()
          puts "print"
        when 228 # printline()
          puts "printline"
        when 215 # read()
          puts "read"
        when 224 # return
          puts "return"
        when 197 # and
          puts "and"
        when 225 # or
          puts "or"
        when 212 # abs()
          puts "abs" 
        when 214 # cos()
          puts "cos" 
        when 225 # sin()
          puts "sin" 
        when 211 # log
          puts "log" 
        when 226 # tan()
          puts "tan" 
        when 231 # sqrt()
          puts "sqrt"
        when 166 # RET
          puts "RET"
        when 217 # true
          puts "true"
        when 203 # false
          puts "false"
        when 61 # =
          puts "="
        when 122 # ==
          puts "=="
        when 60 # <
          puts "<"
        when 62 # >
          puts ">"
        when 123 # <>
          puts "<>"
        when 43 # +
          puts "mas"
        when 45 # -
          puts "menos"
        when 42 # *
          puts "por"
        when 47 # /
          puts "entre"
        when 94 # ^
          puts "^"
        when 107 # ->
          puts "->"
        when 33 # !
          puts "!"
      end
    end
  end
  
end