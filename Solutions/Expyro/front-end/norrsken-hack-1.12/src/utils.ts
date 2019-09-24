export type Product = {
  id: string;
  name: string;
  expiration: number;
  info?: string;
};

export type Dinner = {
  id: string;
  name: string;
  foods: Product[];
  description?: string;
};

export type Provider = {
  id: string;
  name: string;
  logo: string;
};

const flour = {
  id: "test-product-1",
  name: "All purpose flour",
  expiration: 0,
  info: "If your flour has bugs in it. You should probably not eat it."
};
const milk = {
  id: "test-product-2",
  name: "Milk",
  expiration: 0,
  info:
    "Milk should be stored in a cool place. Does it smell bad? No? Then drink it!"
};
const egg = {
  id: "test-product-3",
  name: "Egg",
  expiration: 0,
  info:
    "If you put an egg in a glass of water and it floats, it have turned bad"
};

export const mockedDinners = [
  {
    id: "test-dinner-1",
    name: "Pancake",
    foods: [flour, milk, egg, egg],
    description:
      "1. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam hendrerit nisi sed sollicitudin pellentesque. Nunc posuere purus rhoncus pulvinar aliquam. Ut aliquet tristique 2. nisl vitae volutpat. Nulla aliquet porttitor venenatis. Donec a dui et dui fringilla consectetur id nec massa. 3. Aliquam erat volutpat. Sed ut dui ut lacus dictum fermentum vel tincidunt neque. Sed sed lacinia lectus. Duis sit amet sodales felis. Duis nunc eros, 4. 500°C (!) at dui ac, convallis semper risus. In adipiscing ultrices tellus, in suscipit massa vehicula eu."
  },
  {
    id: "test-dinner-2",
    name: "Omelette",
    foods: [egg, egg, egg, egg],
    description:
      "1. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam hendrerit nisi sed sollicitudin pellentesque. Nunc posuere purus rhoncus pulvinar aliquam. Ut aliquet tristique 2. nisl vitae volutpat. Nulla aliquet porttitor venenatis. Donec a dui et dui fringilla consectetur id nec massa. 3. Aliquam erat volutpat. Sed ut dui ut lacus dictum fermentum vel tincidunt neque. Sed sed lacinia lectus. Duis sit amet sodales felis. Duis nunc eros, 4. 500°C (!) at dui ac, convallis semper risus. In adipiscing ultrices tellus, in suscipit massa vehicula eu."
  },
  {
    id: "test-dinner-3",
    name: "Milk soup",
    foods: [milk, milk, milk],
    description:
      "1. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam hendrerit nisi sed sollicitudin pellentesque. Nunc posuere purus rhoncus pulvinar aliquam. Ut aliquet tristique 2. nisl vitae volutpat. Nulla aliquet porttitor venenatis. Donec a dui et dui fringilla consectetur id nec massa. 3. Aliquam erat volutpat. Sed ut dui ut lacus dictum fermentum vel tincidunt neque. Sed sed lacinia lectus. Duis sit amet sodales felis. Duis nunc eros, 4. 500°C (!) at dui ac, convallis semper risus. In adipiscing ultrices tellus, in suscipit massa vehicula eu."
  }
];

export const mockedProducts = [egg, milk, flour];
