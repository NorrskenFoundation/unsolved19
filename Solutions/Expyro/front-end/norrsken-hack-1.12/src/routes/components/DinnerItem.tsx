import React from 'react';

type Props = {
  name: string;
  onClick(): void;
};

const DinnerItem = ({ name, onClick }: Props) => {
  return (
    <div onClick={onClick} className='List-item'>
      {name}
    </div>
  );
};

export default DinnerItem;
