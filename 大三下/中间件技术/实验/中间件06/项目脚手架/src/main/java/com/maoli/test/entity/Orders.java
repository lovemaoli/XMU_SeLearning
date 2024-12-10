package com.maoli.test.entity;

public class Orders {
    private Integer id;
    private String customer;
    private Integer price;

    public Integer getId() {
        return id;
    }

    public Orders(Integer id, String customer, Integer price) {
        this.id = id;
        this.customer = customer;
        this.price = price;
    }

    public void setId(Integer id) {
        this.id = id;
    }


    public String getCustomer() {
        return customer;
    }

    public void setCustomer(String customer) {
        this.customer = customer;
    }

    public Integer getPrice() {
        return price;
    }

    public void setPrice(Integer price) {
        this.price = price;
    }
}
