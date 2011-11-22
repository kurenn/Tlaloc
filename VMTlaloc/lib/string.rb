class String
  
  def rchomp
    self.chomp("\"").reverse.chomp("\"").reverse
  end
  
end