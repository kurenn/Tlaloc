class Stack
  attr_reader :stack
  
  def initialize
    @stack = []
  end
  
  def push(int, decimal, boolean, string, t_int, t_decimal, t_boolean )
        int = int.clone
        decimal = decimal.clone
        boolean = boolean.clone
        string = string.clone
        t_int = t_int.clone
        t_decimal = t_decimal.clone
        t_boolean = t_boolean.clone
        @stack.push([int,decimal,boolean,string,t_int,t_decimal,t_boolean])
  end
  
  def pop
    @stack.pop
  end
  
  def push_persistance(persistance)
    @stack.last << persistance
  end
  
end