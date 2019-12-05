import React, { useState } from "react";
import ProductItem from "./ProductItem";
import { Product } from "../../utils";
import ProductDialog from "./ProductDialog";

type Props = {
  products: Product[];
};

const ProductList = ({ products }: Props) => {
  const [product, setProduct] = useState<Product | undefined>(undefined);
  const [dialogIsOpen, setDialogIsOpen] = useState(false);

  const showProductInfo = (product: Product) => {
    setProduct(product);
    setDialogIsOpen(true);
  };

  if (products.length < 1) {
    return (
      <h3>No products found. Try adding a product using the button below!</h3>
    );
  }

  return (
    <div style={{ flex: "auto", padding: "20px" }}>
      <h2>Your Ingredients</h2>
      {products.map(d => (
        <ProductItem
          name={d.name}
          expiration={d.expiration}
          key={d.id}
          onClick={() => showProductInfo(d)}
        />
      ))}
      <ProductDialog
        isOpen={dialogIsOpen}
        hideDialog={() => setDialogIsOpen(false)}
        product={product}
      />
    </div>
  );
};

export default ProductList;
