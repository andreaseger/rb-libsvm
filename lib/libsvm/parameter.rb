module Libsvm
  class SvmParameter
    # Constructor sets up values of attributes based on provided map.
    # Valid keys with their default values:
    # * :svm_type = Parameter::C_SVC, for the type of SVM
    # * :kernel_type = Parameter::LINEAR, for the type of kernel
    # * :cost = 1.0, for the cost or C parameter
    # * :gamma = 0.0, for the gamma parameter in kernel
    # * :degree = 1, for polynomial kernel
    # * :coef0 = 0.0, for polynomial/sigmoid kernels
    # * :eps = 0.001, for stopping criterion
    # * :nr_weight = 0, for C_SVC
    # * :nu = 0.5, used for NU_SVC, ONE_CLASS and NU_SVR. Nu must be in (0,1]
    # * :p = 0.1, used for EPSILON_SVR
    # * :shrinking = 1, use the shrinking heuristics
    # * :probability = 0, use the probability estimates
    def initialize args
      super()
      self.svm_type    = args.fetch(:svm_type, SvmType::C_SVC)
      self.kernel_type = args.fetch(:kernel_type, KernelType::LINEAR)
      self.C           = args.fetch(:cost, 1.0)
      self.gamma       = args.fetch(:gamma, 0.0)
      self.degree      = args.fetch(:degree, 1)
      self.coef0       = args.fetch(:coef0, 0.0)
      self.eps         = args.fetch(:eps, 0.001)
      self.nr_weight   = args.fetch(:nr_weight, 0)
      self.nu          = args.fetch(:nu, 0.5)
      self.p           = args.fetch(:p, 0.1)
      self.shrinking   = args.fetch(:shrinking, 1)
      self.probability = args.fetch(:probability, 0)

      unless self.nu > 0.0 and self.nu <= 1.0
        raise ArgumentError "Invalid value of nu #{self.nu}, should be in (0,1]"
      end
    end
  end
end