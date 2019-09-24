class HomeController < ApplicationController
  def index
    render json: { greeting: "Hello, this is API backend for Unsolved 2019 (team 1.12) user_id: #{current_user.id}" }
  end
end
