import React from "react";
import { Product } from "../../utils";
import DialogTitle from "@material-ui/core/DialogTitle";
import Dialog from "@material-ui/core/Dialog";
import { Button } from "@material-ui/core";

type Props = {
  isOpen: boolean;
  hideDialog(): void;
  product?: Product;
};

const infoStyle = {
  marginBottom: "20px"
};

const contentStyles = {
  display: "flex",
  alignItems: "center",
  justifyContent: "center",
  width: "500px",
  flexDirection: "column" as "column"
};

const infoWrapStyle = {
  paddingLeft: "20px",
  paddingRight: "20px",
  display: "flex",
  alignItems: "start",
  justifyContent: "center",
  flexDirection: "column" as "column"
};

const ProductDialog = ({ isOpen, hideDialog, product }: Props) => {
  if (!product) {
    return null;
  }

  return (
    <Dialog
      onClose={hideDialog}
      aria-labelledby="simple-dialog-title"
      open={isOpen}
    >
      <div style={contentStyles}>
        <DialogTitle id="simple-dialog-title">{product.name}</DialogTitle>
        <div style={infoWrapStyle}>
          <b>General info</b>
          <div style={infoStyle}>{product.info}</div>
          <b>Expire date</b>
          <div style={infoStyle}>Your {product.name} expires tomorrow</div>
        </div>
      </div>
      <Button onClick={hideDialog}>Close</Button>
    </Dialog>
  );
};

export default ProductDialog;
