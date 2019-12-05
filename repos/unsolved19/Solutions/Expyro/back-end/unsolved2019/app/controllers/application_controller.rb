class ApplicationController < ActionController::API
  before_action :init_session
  after_action :set_access_control_headers

  private

  def init_session
    user_id = session[:user_id]
    user = User.find_or_create_by id: user_id

    Purchase.generate(user) if user.purchases.none?

    session[:user_id] = user.id
  end

  def current_user
    @current_user ||= User.find session[:user_id]
  end

  def set_access_control_headers
    headers['Access-Control-Allow-Origin'] = '*'
    headers['Access-Control-Request-Method'] = '*'
  end
end
