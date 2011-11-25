class Stack

  attr_reader :stack

  def initialize
    @stack = []
  end
  
  def push(variables, i)
    @stack.push([variables.clone, i])
  end
  
  def pop
    @stack.pop
  end
  
end