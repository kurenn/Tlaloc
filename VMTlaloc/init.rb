TLALOC_ROOT = File.dirname(__FILE__)

#require File.join(TLALOC_ROOT, 'lib', 'vm.rb')
$:.unshift(File.join(TLALOC_ROOT, 'lib'))
require 'vm'

vm = VirtualMachine.new("test.txt")
vm.launch!