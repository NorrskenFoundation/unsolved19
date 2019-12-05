import React from 'react';

type Props = {
  name: string;
  expiration: number;
  onClick(): void;
};

const ProductItem = ({ name, expiration, onClick }: Props) => {
  return (
    <div onClick={onClick} className='List-item'>
      {name}, {expiration}
    </div>
  );
};

export default ProductItem;
