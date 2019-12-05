Rails.application.routes.draw do
  root to: 'home#index'
  resources :products, only: [:index]
  resources :recipes, only: [:index]
end
