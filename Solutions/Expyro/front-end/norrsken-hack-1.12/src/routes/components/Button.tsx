import React, { MouseEvent } from 'react';

type Props = {
  onClick: Function;
};

const Button: React.FC<Props> = ({ children, onClick }) => {
  const handleClick = (event: MouseEvent) => {
    event.preventDefault();
    onClick();
  };

  return <button onClick={handleClick}>{children}</button>;
};

export default Button;
