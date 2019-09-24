food = [
  ['bread', 'short'],
  ['eggs', 'medium'],
  ['fish', 'short'],
  ['avocado', 'medium'],
  ['pumpkin', 'medium'],
  ['milk', 'short'],
  ['oranges', 'medium'],
  ['fungi', 'short'],
  ['rise', 'long'],
  ['pasta', 'long'],
  ['cheese', 'short'],
  ['white rise', 'long'],
  ['pork meat', 'short']
]

food.each { |f, t| Food.seed { |s| s.name = f; s.expiration = t.to_sym } }

